/*

This program will numerically compute the integral of

4/(1+x*x) 

from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

*/

#include <stdio.h>
#include <omp.h>

#define MAX_THREADS 16 

static long num_steps = 100000000;
double step;
int main ()
{
	int i,j;
	double x, pi, sum = 0.0;
	double start_time, run_time;

	step = 1.0/(double) num_steps;


	for(j=1;j<=MAX_THREADS ;j++){
		omp_set_num_threads(j);
		sum = 0.0;
		start_time = omp_get_wtime();
                #pragma omp parallel for reduction (+:sum) private(x) 
		for (i=0; i< num_steps; i++){
			x = (i+0.5)*step;
			sum += 4.0/(1.0+x*x);
		}

		pi = step * sum;
		run_time = omp_get_wtime() - start_time;
		printf("\n pi is %f in %f seconds %d threads \n",pi,run_time,j);
	}
}	  





