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
<<<<<<< HEAD
=======
		//std::cout << "Passo6" << std::endl;
		for (int i = 0; i < Task::__ready.length(); i++) {
			std::cout << i << std::endl;
		}
    	while (Task::__ready.length() > 0) {
			Task *next = Scheduler::self()->choose_next(); 	

			// std::cout << Task::count() << std::endl;
>>>>>>> d825766c413cac079f394be296ed8d8a6fbd553f

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
<<<<<<< HEAD
		Task* elem = (Task*) __ready.remove();
		return elem;
=======
		// Task* zoa;/* = (Task*) Task::ready().remove();*/
		return (Task*) Task::__ready.remove();
		// while (__ready.length() > 0) {
		// 	std::cout << "Tid: " << zoa->tid() << std::endl;
		// 	// std::sleep(1000);
		// 	//usleep(10000);
		// }
		//std::cout << "Tid da Task que foi retirada: " << zoa->tid() << std::endl;
		// return zoa;
>>>>>>> d825766c413cac079f394be296ed8d8a6fbd553f
	}



}


#endif