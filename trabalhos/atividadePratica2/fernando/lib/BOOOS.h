/*
 * BOOOS.h
 *
 *  Created on: Aug 14, 2014
 */

#ifndef BOOOS_H_
#define BOOOS_H_

namespace BOOOS {

/* Configuration Space */

class BOOOS {
public:
	BOOOS(bool verbose = true);
	~BOOOS();

	// static const int BOOOS_VERSION = 0;
	// static const BOOOS * __booos = 0;
	// static const SCHED_TYPE SCHED_POLICY = SCHED_FCFS; // ou outro escalonador. Ajustem como necessário
	// static const bool SCHED_PREEMPT = false;  // pode ser preemptivo ou não
	// static const bool SCHED_AGING = false; 
	void panic();

private:
	bool _verbose;
};

} /* namespace BOOOS */

#endif /* BOOOS_H_ */
