/*
 * Task.h
 *
 *  Created on: Aug 15, 2014
 */

#ifndef TASK_H_
#define TASK_H_

#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

namespace BOOOS {

	class Task : public Queue::Element {
	 public:
		enum State {
			READY,
			WAITING,
			RUNNING,
			FINISHING
		};

		Task(void (entry_point)(void*), int nargs, void * arg);

		virtual ~Task();

		int tid() { return _tid; }
		State state() { return _state; }

		void pass_to(Task * t, State s = READY);

		void exit(int code);

		static Task * self() { return (Task*) __running; }
		static void init();

	 private:

		Task();

		static volatile Task * __running;
		static Task * __main;
		ucontext_t* getContx() {
			return &_context;
		}
		State _state;
		int _tid; // task ID
		ucontext_t _context;
		char* _stack;
		static int __tid_counter;
		static const int stackSize = 32768;
	};

}

#endif /* TASK_H_ */
