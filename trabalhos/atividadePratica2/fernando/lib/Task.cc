/* Emmanuel Podestá Junior, Fernando Paladini.
 * Task.cc
 *
 *  Created on: Feb 27, 2014
 */

#include "Task.h"

namespace BOOOS
{

	volatile Task * Task::__running;
	Task * Task::__main;
	int Task::__tid_counter;
	Queue __ready;
	const int _STACK_SIZE = 32768;

	Task::Task() {
		this->_tid = 0;
		this->allocate_stack();
	}

	Task::Task(void (*entry_point)(void*), int nargs, void * arg) {
		this->_tid = ++Task::__tid_counter;
		this->_state = Task::READY;
		getcontext(&(this->_context));
		this->_context.uc_link = (ucontext_t*)&__running->_context;
		this->allocate_stack();

		// Adding to queue
		__ready.insert(&this);

		makecontext(&(this->_context), (void (*)(void)) entry_point, nargs, arg);
	}

	Task::~Task() {
		delete this->_stack;
	}

	void Task::init() {
		__main = new Task();
		__main->_state = Task::RUNNING;
		__running = __main;
		__tid_counter = 1;
	}

	void Task::yield() {
		pass_to(&this, Task::SCHEDULER); // arumar, não é this, tem que passar para o escalonador.
	}

	void Task::pass_to(Task * t, State s) {
		this->_state = s;
		__running = t;
		__running->_state = RUNNING;
		swapcontext(&(this->_context), &(t->_context));
	}

	void Task::exit(int code) {
		// Removing the task from ready queue.
		__ready.remove(this);

		this->pass_to(Task::__main, Task::FINISHING);
	}

	void Task::allocate_stack() {
		this->_stack = new char[Task::_STACK_SIZE];
		this->_context.uc_stack.ss_sp = _stack;
		this->_context.uc_stack.ss_size = Task::_STACK_SIZE;
	}

} /* namespace BOOOS */
