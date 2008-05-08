#include "timer.h"
#include <stdio.h>
void pr_times_stdout(double time);

void testTimer(){
	int i;
	start_timer();
	for( i=0 ; i<1000000000 ; i++)
		;
	pr_times_stdout(get_timer());
	
	
}


void pr_times_stdout(double time){
    static int no=1;

    printf("%d \t%.6f\n",no++,time);

}

