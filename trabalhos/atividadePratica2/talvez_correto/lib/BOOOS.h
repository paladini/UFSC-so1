/*
 * BOOOS.h
 *
 *  Created on: Mar 24, 2014
 *      Author: arliones
 */

#ifndef BOOOS_H_
#define BOOOS_H_

#include "BOOOS.h"
#include "Timer.h"
#include "Scheduler.h"

namespace BOOOS {

/* Configuration Space */
class BOOOS_Configuration {
public:
	static Scheduler::SchedulerType SCHEDULER_TYPE;
	static bool SCHEDULER_PREEMPT;
	static bool SCHEDULER_AGING;
	static Timer::Timestamp TIMER_RESOLUTION; // in microseconds / tick
	static Timer::Timestamp SCHEDULER_RESOLUTION; // in ticks / queue check
	static Timer::Timestamp SCHEDULER_QUANTUM; // in ticks / task
};

void init();

} /* namespace BOOOS */

#endif /* BOOOS_H_ */