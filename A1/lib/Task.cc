/*
 * Task.cc
 *
 *  Created on: Feb 27, 2014
 */
#ifndef TASK_CC_
#define TASK_CC_

#include "Task.h"

namespace BOOOS
{

	volatile Task * Task::__running;
	volatile Task * Task::__main;
/*
 * Task.h
 *
 *  Created on: Aug 15, 2014
 */
 	Task::Task() {
 		this->_context = new ucontext_t;
 		this->_tid = 0;
		this->_context->uc_stack.ss_sp = _stack;
		this->_context->uc_stack.ss_size = sizeof(_stack);
	}
	Task::Task(void (entry_point)(void*), int nargs, void * arg) {
		this->_state = READY;
		this->_tid = Task::tidCounter++;
		this->_context = new ucontext_t;
		this->_stack = new char[this->stackSize]();
		//this->_context->uc_link = __main;
		this->_context->uc_stack.ss_sp = _stack;
		this->_context->uc_stack.ss_size = sizeof(_stack);
		makecontext(this->_context, (void (*)(void)) entry_point, nargs, arg);
	}
	Task::~Task() {
		//delete[] _stack;
		//delete[] _context;
	}

	void Task::pass_to(Task * t, State s) {
		this->_state = s;
		__running = t;
		swapcontext((this->_context), (t->_context));
	}

	void Task::exit(int code) {
		this->exit(0);
	}

	void Task::init() {
		__main = new Task();
 		__main->_state = RUNNING;
		__running = __main;
		Task::tidCounter = 0;
	}
	// ...

} /* namespace BOOOS */

#endif /* TASK_CC_ */
