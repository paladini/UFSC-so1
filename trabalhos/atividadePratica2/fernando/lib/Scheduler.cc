/* 	Emmanuel Podestá Junior, Fernando Paladini.
 * 	Scheduler.cc
 *
 *  Created on: Aug 14, 2014
 */
#ifndef SCHEDULER_CC_
#define SCHEDULER_CC_
#include "Scheduler.h"
#include "Task.h"
#include <iostream>

namespace BOOOS {

	Scheduler* Scheduler::__dispatcher = 0;

	Scheduler::Scheduler() : Task(dispatcher, 0, 0) { 
		this->setState(Task::SCHEDULER);
	}
	Scheduler::~Scheduler() {
		delete __dispatcher;
	}

	void Scheduler::init() {
		if (__dispatcher == 0) {
			__dispatcher = new Scheduler();
		}
	}
	Scheduler* Scheduler::self() {
		return __dispatcher;
	}
	void Scheduler::dispatcher(void*) {

    	while (__ready.length() > 0) {
			Task *next = self()->choose_next();
			if (next) {
				Scheduler::self()->pass_to(next);
			}
			if (Task::self()->state() == Task::RUNNING) {
				Task::self()->exit(0);
			}

		} 
		Scheduler::self()->exit(0);
	}  
	Task * Scheduler::choose_next() {
		Task* elem = (Task*) __ready.remove();
		return elem;

	}



}


#endif