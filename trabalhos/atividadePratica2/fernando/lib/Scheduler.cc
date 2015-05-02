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

	Scheduler* Scheduler::__dispatcher;

	Scheduler::Scheduler() : Task(dispatcher, 1, 0) { 
		this->setState(Task::SCHEDULER);
	}
	Scheduler::~Scheduler() {
		delete __dispatcher;
	}

	void Scheduler::init() {
		Task::init();
		__dispatcher = new Scheduler();
		//this->yield();
		__dispatcher->setTid(1);
	}
	Scheduler* Scheduler::self() {
		return __dispatcher;
	}
	void Scheduler::dispatcher(void*) {
    	while (Scheduler::ready().length() > 0) {
			Task *next = Scheduler::self()->choose_next(); 	
			if (next) {
				Task::self()->pass_to(next, Task::READY);
				Scheduler::ready().insert(next);
			}
		} 
		Task::self()->exit(0);
	}
	Task * Scheduler::choose_next() {
		return (Task*) Scheduler::ready().remove();
	}
	



}


#endif