#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv) {
	int p = atoi(argv[1]);
	//omp_set_num_threads(p);
#pragma omp parallel num_threads(p)
	{
		printf("Hello World from %d\n", omp_get_thread_num());
	}

	//omp_set_num_threads(p/2);
#pragma omp parallel num_threads(p/2) 
	{
		printf("Hello World a second time from %d\n", omp_get_thread_num());
	}

	return 0;
}
