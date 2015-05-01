/*
 * BOOOS.h
 *
 *  Created on: Aug 14, 2014
 */

#ifndef BOOOS_H_
#define BOOOS_H_
// #include "Scheduler.h"

namespace BOOOS {

/* Configuration Space */

class BOOOS {

public:

    //using Scheduler::SchedulerType; - try solve that later.
	enum SchedulerType {
		SCHED_FCFS,
		SCHED_PRIORITY
	};

	BOOOS(bool verbose = true);
	~BOOOS();

	// static const int BOOOS_VERSION = 0;
	static BOOOS * __booos;
	static BOOOS::SchedulerType SCHED_POLICY; // ou outro escalonador. Ajustem como necessário
	static bool SCHED_PREEMPT;  // pode ser preemptivo ou não
	static bool SCHED_AGING; 
	void panic();

private:
	bool _verbose;
};

} /* namespace BOOOS */

#endif /* BOOOS_H_ */
