//This file was generated from (Academic) UPPAAL 4.0.13 (rev. 4577), September 2010

/*

*/
A[] not ((Process0.criticalregion and Process1.criticalregion) or (Process0.criticalregion and Process2.criticalregion) or (Process0.criticalregion and Process3.criticalregion) or \
(Process1.criticalregion and Process2.criticalregion) or (Process1.criticalregion and Process3.criticalregion) or\
(Process2.criticalregion and Process3.criticalregion))

/*

*/
A[] not deadlock
