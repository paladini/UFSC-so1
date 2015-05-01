/* 	Emmanuel Podestá Junior, Fernando Paladini.
 * 	Scheduler.cc
 *
 *  Created on: Aug 14, 2014
 */
#ifndef SCHEDULER_CC_
#define SCHEDULER_CC_
#include "Scheduler.h"
namespace BOOOS {

	Scheduler::Scheduler() {
		Scheduler scheduler = new Task(this->dispatcher(),); // 
		this->_state = Task::SCHEDULER;
	}
	Scheduler::~Scheduler() {}

	void init() {
		__dispatcher = new Scheduler();
		__dispatcher->_tid = 1;
	}

	void dispatcher() {
    	int userTasks = __ready.length();
	    while(userTasks > 0) {
	       Task *next = choose_next() ;  // escolher a próxima Task* a executar
	       if(next != NULL)
	       {
	          ... // ações antes de lancar a tarefa "next", se houverem
	          self()->pass_to(next); // transfere controle para a tarefa "next"
	          ... // ações apos retornar da tarefa "next", se houverem
	       }
	    }
	    exit(0) ; // encerra a tarefa dispatcher
	}

	Task * choose_next() {
		Task* task = __ready.remove();
		__ready.insert(task);
		return task;
	}
	



}


#endif