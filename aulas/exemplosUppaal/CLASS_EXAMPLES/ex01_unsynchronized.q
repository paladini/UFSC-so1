//This file was generated from (Academic) UPPAAL 4.0.13 (rev. 4577), September 2010

/*

*/
Process0.done --> Process0.i == iterations

/*

*/
Process1.done --> Process1.i == iterations

/*

*/
A[]  not deadlock

/*

*/
A[] not (Process0.criticalregion and Process1.criticalregion)

/*

*/
E<> Process0.done

/*

*/
E<> Process1.done
