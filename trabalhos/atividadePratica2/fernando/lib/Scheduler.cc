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
    	while (Task::ready().length() > 0) {
			Task *next = self()->choose_next(); 	
			
			if (next) {
				Task::self()->pass_to(next);
			}
		} 
		Task::self()->exit(0);
	}
	Task * Scheduler::choose_next() {
		return (Task*) Task::ready().remove();
	}
	



}


#endif