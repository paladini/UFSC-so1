/* Emmanuel Podestá Junior, Fernando Paladini.
 * Task.cc
 *
 *  Created on: Feb 27, 2014
 */
#ifndef TASK_CC_
#define TASK_CC_
#include "Task.h"
#include "Scheduler.h"
#include "BOOOS.h"
#include <iostream>

namespace BOOOS {

	volatile Task * Task::__running;
	Task * Task::__main;
	int Task::__tid_counter;
	int Task::__task_counter;
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
		this->_state = READY;
		this->allocate_stack();
		makecontext(&(this->_context), (void (*)(void)) entry_point, nargs, arg);
		this->_tid = __tid_counter;
		if (nargs > 0) {
			// __ready.insert(this);
			insert_ready(this);
		}
		__task_counter++;
		__tid_counter++;
	}

	Task::~Task() {
		if (this->_state == RUNNING){
			Task::self()->exit(0);
		}
		if (this->_state == READY) {
			if (__ready.searchB(this)) {
				__ready.remove(this);
				__task_counter--;
			}
		}
		delete[] this->_stack;
	}

	void Task::init() {
		__tid_counter = 0;
		__task_counter = 0;
		__main = new Task();
		__main->_state = Task::RUNNING;
		__running = __main;
	}


	void Task::yield() {
		this->pass_to(Scheduler::__dispatcher, READY);
	}

	void Task::pass_to(Task * t, State s) {

		if (t->_state != SCHEDULER) {
			t->_state = RUNNING;
		}

		if (this->_state != SCHEDULER) {
			this->_state = s;

			if (s == FINISHING) {
				if (__ready.searchB(this)) {
					__ready.remove(this);
				}
				
			}
			if (s == READY) {
				if (!__ready.searchB(this)) {
<<<<<<< HEAD
					__ready.insert(this);
=======
					//std::cout << "READY"<< this->_tid << std::endl;
					//__ready.insert(this);
					insert_ready(this);
					//__task_counter++;
>>>>>>> d825766c413cac079f394be296ed8d8a6fbd553f
				}
			}
		}

		__running = t;

		swapcontext(&(this->_context), &(t->_context));
	}

	void Task::exit(int code) {
		__task_counter--;

		if (this->_state == SCHEDULER) {
			this->pass_to(__main, FINISHING);
		} else {
			this->pass_to(Scheduler::__dispatcher, FINISHING);
		}

	}

	void Task::allocate_stack() {
		this->_stack = new char[_STACK_SIZE];
		this->_context.uc_stack.ss_sp = _stack;
		this->_context.uc_stack.ss_size = _STACK_SIZE;
		this->_context.uc_stack.ss_flags = 0;
		this->_context.uc_link = (ucontext_t*)&(Scheduler::__dispatcher)->_context;

	}

	void Task::nice(int priority) {
		if (-20 <= priority <= 20) {
			this->rank(priority);
		}
	}

	void Task::insert_ready(Task* t) {
		if (BOOOS::SCHED_POLICY == BOOOS::SCHED_PRIORITY) {
			Task::__ready.insert_ordered(t);
		} else if (BOOOS::SCHED_POLICY == BOOOS::SCHED_FCFS) {
			Task::__ready.insert(t);
		}
	}

} /* namespace BOOOS */
#endif