/* Emmanuel Podestá Junior, Fernando Paladini.
 * Task.h
 *
 *  Created on: Aug 15, 2014
 */

#ifndef TASK_H_
#define TASK_H_

#include <Queue.h>
#include <ucontext.h>

namespace BOOOS {

class Task : public Queue::Element {
public:
	enum State {
		READY,
		WAITING,
		RUNNING,
		FINISHING,
		SCHEDULER
	};

	Task(void (*entry_point)(void), int nargs, void * arg);
	Task(void (*entry_point)(void*), int nargs, void * arg);
	virtual ~Task();

	int tid() { return _tid; }
	State state() { return _state; }

	void yield();
	void pass_to(Task * t, State s = READY);
	void exit(int code);

	static Task * self() { return (Task*) __running; }
	static void init();

private:

	Task();
	void allocate_stack();

	static volatile Task * __running;
	static Task * __main;
	static int __tid_counter;
	static Queue __ready;
	static const int _STACK_SIZE = 32768;

	State _state;
	int _tid; // task ID
	ucontext_t _context;
	char* _stack;

};

} /* namespace BOOOS */

#endif /* TASK_H_ */
