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
		//std::cout << "Passo6" << std::endl;
		for (int i = 0; i < self()->ready().length(); i++) {
			std::cout << i << std::endl;
		}
    	while (Task::self()->ready().length() > 0) {
			Task *next = Task::self()->choose_next(); 	

			std::cout << Task::count() << std::endl;

			if (next) {
				//std::cout << "Passo7" << std::endl;
				Scheduler::self()->pass_to(next);
			}
			//std::cout << "Zue" << std::endl;
			if (Task::self()->state() == Task::RUNNING) {
				Task::self()->exit(0);
			}

		} 
		//std::cout << "Passo8" << std::endl;
		Scheduler::self()->exit(0);
	}
	Task * Scheduler::choose_next() {
		Task* zoa;/* = (Task*) Task::ready().remove();*/
		zoa = (Task*) Task::self()->ready().remove();
		// while (__ready.length() > 0) {
		// 	std::cout << "Tid: " << zoa->tid() << std::endl;
		// 	// std::sleep(1000);
		// 	//usleep(10000);
		// }
		//std::cout << "Tid da Task que foi retirada: " << zoa->tid() << std::endl;
		return zoa;
	}



}


#endif