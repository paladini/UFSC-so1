/* Emmanuel Podestá Junior, Fernando Paladini.
 * Scheduler.h
 *
 *  Created on: Mar 21, 2014
 */
 
#ifndef SCHEDULER_H_
#define SCHEDULER_H_
 
#include "Task.h"
#include "Queue.h"
 
namespace BOOOS {
	 
	class Scheduler : public Task {
		friend class Task;
	 
		protected:
			Scheduler();
		 
		public:
			enum SchedulerType {
				SCHED_FCFS,
				SCHED_PRIORITY
			};
		 
			virtual ~Scheduler();

			static void init();
			static void dispatcher(void*);
			static Scheduler * self();
		 
		protected:
			virtual Task * choose_next();
			static void aging();
			static Scheduler * __dispatcher;
	};
 
} /* namespace BOOOS */
#endif