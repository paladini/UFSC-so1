/*
 * Task.cc
 *
 *  Created on: Feb 27, 2014
 *      Author: arliones
 */
#include "Task.h"
#include "Scheduler.h"
#include "BOOOS.h"
#include <stdio.h>
#include <ucontext.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#define STACKSIZE 32768		/* tamanho de pilha das threads */

using namespace std;

namespace BOOOS {

    volatile Task * Task::__running;
    Task * Task::tMain;
    Queue Task::__ready;
    Queue Task::__sleep;
    volatile int Task::__tid_counter = 0;

    // This method initializes Task's global attributes

    void Task::init() {
        tMain = new Task(0, 0, (char*) "\tMain");
        tMain->_response = Timer::time();
        __running = tMain;
        __running->_activations = 1;
    }

    // This constructor creates a task.
    // - entry_point: pointer to a function that implements the behavior of the task
    // - nargs: number of arguments sent to the entry_point function
    // - arg: vector with the arguments for the entry_point function

    Task::Task(void (*entry_point)(void *), int nargs, void * arg) {

        getcontext(&this->ctask);
        char * stack;
        stack = (char *) malloc(STACKSIZE);
        if (stack) {
            this->_cputime = 0;
            this->_cpuaux = 0;
            this->_coxilo = 0;
            this->_codeExit = 0;
            this->_activations = 0;
            this->_response = Timer::time();
            this->ctask.uc_stack.ss_sp = stack;
            this->ctask.uc_stack.ss_size = STACKSIZE;
            this->ctask.uc_stack.ss_flags = 0;
            this->ctask.uc_link = 0;
            this->_tid = __tid_counter++;
            if (nargs > 0) {
                this->_state = READY;
                insert_in_ready(this);
            } else {
                this->_state = RUNNING;
            }

        } else {
            perror("Erro na criação da pilha: ");
            exit(1);
        }
        if (nargs > 0) {
            makecontext(&(this->ctask), (void(*)(void))entry_point, nargs, arg);
        }

        //inicializar timer do cputime
        //inicializar timer do TR
    }

    // This destructor destroys/frees any resources allocated in the constructor

    Task::~Task() {
        __tid_counter--;

    }

    // This method transfers the execution flow from the current task to the Task 't'.
    // - t: pointer to the task that will assume the CPU.
    // - s: state that the current task will assume

    void Task::pass_to(Task * t, State s) {
        Task * aux = this->self();

        if (__running->_state != SCHEDULER) {
            __running->_cputime = Timer::time() + __running->_cputime - __running->_cpuaux;
            __running->_state = s;
        }
        if (t->_state != SCHEDULER) {
            t->_state = RUNNING;
            t->_cpuaux = Timer::time();
        }
        //t->_activations++;
        __running = t;
        if (__running->_state == RUNNING) {
            __running->_activations++;
        }
        if (aux->_state == READY) {
            insert_in_ready(aux);
        }

        swapcontext(&(aux->ctask), &(t->ctask));
    }

    void Task::insert_in_ready(Task * task) {
        if (BOOOS_Configuration::SCHEDULER_TYPE == Scheduler::SCHED_FCFS) {
            __ready.insert(task);
        }
        if (BOOOS_Configuration::SCHEDULER_TYPE == Scheduler::SCHED_PRIORITY) {
            __ready.insert_ordered(task);
        }
    }

    void Task::yield() {
        pass_to(Scheduler::self());
    }

    // This method finalizes a task
    // - code: exit/error code.

    void Task::exit(int code) {
        __tid_counter--;
        Task * aux;

        this->_codeExit = code;

        while (this->_sleepQueue.length() != 0) {
            aux = (Task *) this->_sleepQueue.remove();
            aux->_state = READY;
            insert_in_ready(aux);
        }
        if (this->state() != SCHEDULER) {
            this->_response = Timer::time() - this->_response;
            cout << "Task " << this->_tid << " exit: response time " << this->_response / 1000 << " ms, CPU time " << this->_cputime / 1000 << " ms, " << this->_activations << " activations" << endl;
            pass_to(Scheduler::self(), FINISHING);
        } else {
            pass_to(tMain, FINISHING);
        }


    }

    int Task::count() {
        return __tid_counter;
    }

    int Task::join(Task * b) {

        if (b == 0) return -1;

        if (b->_state == FINISHING) {
            return b->_codeExit;
        } else {
            if (b == this) return 0;
            //__ready.removeItem(Task::self());
            Task::self()->_state = WAITING;
            b->_sleepQueue.insert(Task::self());
            this->pass_to(Scheduler::self(), WAITING);
            return b->_codeExit;
        }
    }

    void Task::requestWakeup() {
        int aux = Timer::time();
        int cont = 0;
        Task * task;

        if(__sleep.length() == 0) cout << "nada no sleep" << endl;
        while (cont != __sleep.length() + 1) {
            task = (Task *) __sleep.getItem(cont);
            if (task != 0) {
                if (aux >= task->coxilo()) {
                    task->_state = READY;
                    cout << "Acordei" << endl;
                    __sleep.removeItem(task);
                    this->insert_in_ready(task);
                } else {
                    cont++;
                }
            }
        }
        return;
    }

    void Task::sleep(int t) {
        int aux = 0;
        
        if (t != 0) {
            //__ready.removeItem(this);
            this->_state = WAITING;
            __sleep.insert(self());
            aux = Timer::time(); //start
            this->coxilo(aux + t);
            pass_to(Scheduler::__dispatcher);
        } else {
            return;
        }
        return;
    }

} /* namespace BOOOS */
