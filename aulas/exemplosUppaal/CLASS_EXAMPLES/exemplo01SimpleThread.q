//This file was generated from (Commercial) UPPAAL 4.0.14 (rev. 5615), May 2014

/*

*/
A[] not deadlock

/*

*/
A[] not (Process0.criticalRegion and Process1.criticalRegion)

/*

*/
E<> Process1.done

/*

*/
Process1.done --> Process1.i == iterations

/*

*/
Process0.done --> Process0.i == iterations

/*

*/
A[] not deadlock

/*

*/
A[] not ((Process0.criticalRegion and Process1.criticalRegion) or (Process0.criticalRegion and Process2.criticalRegion) or (Process0.criticalRegion and Process3.criticalRegion) or (Process1.criticalRegion and Process2.criticalRegion) or (Process1.criticalRegion and Process3.criticalRegion) or (Process2.criticalRegion and Process3.criticalRegion)
