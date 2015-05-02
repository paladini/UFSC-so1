/*
 * Scheduler.cpp
 *
 *  Created on: Mar 21, 2014
 *      Author: arliones
 */

#include "Task.h"
#include "Scheduler.h"
#include "Timer.h"
#include <ucontext.h>
#include <iostream>
using namespace std;

namespace BOOOS {
    Scheduler * Scheduler::__dispatcher = 0;

    /*
     *  The scheduler is an active task that schedules/manages other tasks
     */
    Scheduler::Scheduler() : Task(dispatcher, 1, 0) {
        //this->_activations = 1;
        this->_state = SCHEDULER;
    }

    Scheduler::~Scheduler() {
    }

    /*
     * Initializes Scheduler's static attributes
     */
    void Scheduler::init() {
        if (__dispatcher == 0) {
            __dispatcher = new Scheduler();
        } else {
            return;
        }


    }

    /*
     * This function implements the scheduler behavior.
     */
    void Scheduler::dispatcher(void*) {
        Task * aux;

        while (__ready.length() > 0) {
            aux = __dispatcher->choose_next(); // escolher a próxima Task* a executar
            if (aux) {
                if (aux->state() != SCHEDULER) {
                    self()->pass_to(aux); // transfere controle para a tarefa "next"  
                }
            }
        }
        __dispatcher->exit(0); // encerra a tarefa dispatcher
    }

    void Scheduler::notify_time(Timer::Timestamp ticks) {
        this->requestWakeup();
        this->yield();
    }

    Task * Scheduler::choose_next() {
        return (Task*) __ready.remove();
    }

} /* namespace BOOOS */
