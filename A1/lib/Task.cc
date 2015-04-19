/*
 * Task.cc
 *
 *  Created on: Feb 27, 2014
 */
#ifndef TASK_CC_
#define TASK_CC_

#include "Task.h"
#include <iostream>

namespace BOOOS
{
	int Task::_tidCounter;
	const int stackSize = 32768;
	volatile Task * Task::__running;
	Task * Task::__main;

 	Task::Task() {
 		getcontext(&(this->_context));
 		this->_tid = 0;
 		this->_stack = new char[this->stackSize];
		this->_context.uc_stack.ss_sp = _stack;
		this->_context.uc_stack.ss_size = stackSize;
	}

	Task::Task(void (entry_point)(void*), int nargs, void * arg) {
		this->_state = Task::READY;
		this->_tid = Task::_tidCounter++;
		getcontext(&(this->_context));
		this->_context.uc_link = &__main->_context;
		this->_stack = new char[this->stackSize];
		this->_context.uc_stack.ss_sp = _stack;
		this->_context.uc_stack.ss_size = stackSize;
		makecontext(&(this->_context), (void (*)(void)) entry_point, nargs, arg);
	}

	Task::~Task() {
		delete this->_stack;
	}

	void Task::pass_to(Task * t, State s) {
		this->_state = s;
		__running = t;
		__running->_state = RUNNING;
		swapcontext(&(this->_context), &t->_context);
	}

	void Task::exit(int code) {
		this->pass_to(Task::__main, Task::FINISHING);
	}

	void Task::init() {
		__main = new Task();
 		__main->_state = RUNNING;
		__running = __main;
		Task::_tidCounter = 1;
	}

}

#endif /* TASK_CC_ */
