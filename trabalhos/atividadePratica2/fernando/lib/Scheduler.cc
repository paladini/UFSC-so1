/* 	Emmanuel Podestá Junior, Fernando Paladini.
 * 	Scheduler.cc
 *
 *  Created on: Aug 14, 2014
 */
#ifndef SCHEDULER_CC_
#define SCHEDULER_CC_
#include "Scheduler.h"
#include <iostream>

namespace BOOOS {

	Scheduler* Scheduler::__dispatcher = NULL;

	Scheduler::Scheduler() : Task(Scheduler::dispatcher, 0, 0) { 
		this->setState(Task::SCHEDULER);
	}
	Scheduler::~Scheduler() {}

	void Scheduler::init() {
		__dispatcher = new Scheduler();
		__dispatcher->setTid(1);
	}
	Scheduler* Scheduler::self() {
		return __dispatcher;
	}
	void Scheduler::dispatcher(void*) {
    	while (Scheduler::ready().length() > 0) {
			Task *next = Scheduler::self()->choose_next(); 	
			if (next) {
				Scheduler::ready().insert(next);
				Scheduler::self()->pass_to(next, Task::READY);
			}
		} 
		Scheduler::self()->exit(0);
	}
	Task * Scheduler::choose_next() {
		return (Task*) Scheduler::ready().remove();
	}
	



}


#endif