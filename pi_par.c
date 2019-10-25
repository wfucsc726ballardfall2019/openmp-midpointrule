/*

   This program will numerically compute the integral of

   4/(1+x*x) 

   from 0 to 1.  The value of this integral is pi -- which 
   is great since it gives us an easy way to check the answer.

*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
static long num_steps = 100000000;
double step;
int main (int argc, char** argv)
{
	int i;
	double x, pi, sum = 0.0;
	double start_time, run_time;
	int np = atoi(argv[1]);
	omp_set_num_threads(np);
	step = 1.0/(double) num_steps;

	start_time = omp_get_wtime();

#pragma omp parallel private(i,x) 
	{
		int id = omp_get_thread_num();
		double lsum = 0.0;
		for (i=id+1;i<= num_steps; i+=np){
			x = (i-0.5)*step;
			lsum = lsum + 4.0/(1.0+x*x);
		}
		#pragma omp critical
		sum = sum + lsum;
	}

	pi = step * sum;
	run_time = omp_get_wtime() - start_time;
	printf("\n pi with %ld steps is %lf in %lf seconds\n",num_steps,pi,run_time);
}	  





