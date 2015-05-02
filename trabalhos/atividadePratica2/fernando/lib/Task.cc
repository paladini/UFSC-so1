/* Emmanuel Podestá Junior, Fernando Paladini.
 * Task.cc
 *
 *  Created on: Feb 27, 2014
 */
#ifndef TASK_CC_
#define TASK_CC_
#include "Task.h"
#include "Scheduler.h"
#include <iostream>

namespace BOOOS {

	//Scheduler* Scheduler::__dispatcher;
	volatile Task * Task::__running;
	Task * Task::__main;
	int Task::__tid_counter = 0;
	int Task::__task_counter = 0;
	Queue Task::__ready;
	const int _STACK_SIZE = 32768;

	Task::Task() {
		this->_tid = 0;
		this->allocate_stack();
		__tid_counter++;
		__task_counter++;
	}

	Task::Task(void (*entry_point)(void*), int nargs, void * arg) {
		getcontext(&(this->_context));
		this->_tid = __tid_counter;
		this->_state = READY;

		// Dar uma olhada nesse método, tem um problema.
		this->allocate_stack();
		makecontext(&(this->_context), (void (*)(void)) entry_point, nargs, arg);

		// Adding to queue. Only add to queue if not Scheduler.
		if (nargs > 0) {
			__ready.insert(this);
		}
		
		__task_counter++;
		__tid_counter++;
		
	}

	Task::~Task() {
		if (this->_state != FINISHING){
			Task::exit(0);
		}
		delete this->_stack;
	}

	void Task::init() {
		__tid_counter = 0;
		__task_counter = 0;
		__main = new Task();
		__main->_state = Task::RUNNING;
		__running = __main;
	}

	void Task::yield() {
		this->pass_to(Scheduler::__dispatcher, READY); // arumar, não é this, tem que passar para o escalonador.
	}

	void Task::pass_to(Task * t, State s) {
        // Task * aux = this->self();
		
		if (t->_state != SCHEDULER) {
			t->_state = RUNNING;
		}

		if (this->_state != SCHEDULER) {
			this->_state = s;

			if (s == READY) {
				__ready.insert(this);
			}
		}

		__running = t;

		//std::cout << "tid: " << (this->_tid) << std::endl;
		/* if (this->_state == Task::SCHEDULER) {
			//this->_state = s;
		 	__running = t;
		 	//__ready.insert(this);
		} else {
			this->_state = s;
			__running = t;
			__running->_state = Task::RUNNING;
		}
		bool isScheduler = this->_state == SCHEDULER;
		std::cout << "This task has '_state' == scheduler? " << isScheduler << std::endl; */
		/*if (t->_state == SCHEDULER) {
			this->__running = t;
		} else if (this->_state == SCHEDULER){
			this->_state = s;
			__running = t;
			__running->_state = RUNNING;
		} else {
			this->_state = s;
			__running = t;
			__running->_state = RUNNING;
		} */
		/* __running = t;

		if (this->_state != SCHEDULER) {
			this->_state = s;
			// __running->_state = RUNNING;
		} */

		//std::cout << "More Magic" << std::endl;
		swapcontext(&(this->_context), &(t->_context));
	}

	void Task::exit(int code) {
		__task_counter--;
		__tid_counter--;

		//if (self() != __main) {
			if (this->_state == SCHEDULER) {
				this->pass_to(__main, FINISHING);
			} else {
				this->pass_to(Scheduler::__dispatcher, FINISHING);
			}
		//}
		// Removing the task from ready queue.
		/* __ready.remove(this); */

		//this->pass_to(Task::__main, Task::FINISHING); */
	}

	void Task::allocate_stack() {
		this->_stack = (char*) malloc(_STACK_SIZE);
		this->_context.uc_stack.ss_sp = _stack;
		this->_context.uc_stack.ss_size = _STACK_SIZE;

		// se a linha abaixo for descomentada, os testes dão erro.
		// caso ela esteja comentada e em baixo a outra linha recebendo = 0, passa em tudo.
		this->_context.uc_link = (ucontext_t*)&__running->_context;
		// this->_context.uc_link = 0;
	}

} /* namespace BOOOS */
#endif