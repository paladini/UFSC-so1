//This file was generated from (Academic) UPPAAL 4.0.13 (rev. 4577), September 2010

/*

*/
A[] forall (i:int[0,maxThreads-1]) forall (j:int[0,maxThreads-1]) SimpleThread(i).criticalregion && SimpleThread(j).criticalregion imply i ==j\


/*

*/
A[] not deadlock
