# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <math.h>

void seedThreads(unsigned int* seeds); //Generate unique seeds for each thread.
void computeSave(FILE* res);

int main()
{
	/*FILE *res;

	res = fopen("Data1.csv", "w+");*/

	omp_set_num_threads(4);

	int nThreads = 4;

	//int id;

	unsigned int* seeds = (unsigned int*)malloc(sizeof(int)*nThreads);

	seedThreads(seeds);
	
	//printf("The first seed is %d", seeds[0]);

//#	pragma omp parallel \
//	private(id) shared(seeds)
//	{
//		id = omp_get_thread_num();
//		printf("thread %d has seed %d \n", id, seeds[id]);
//	}



	return 0;
}

void seedThreads(unsigned int* seeds) {

#	pragma omp parallel
	{
		unsigned int threadId = omp_get_thread_num();

		unsigned int seed = (unsigned)time(NULL);

		seeds[threadId] = (seed & 0xFFFFFFF0) | (threadId + 1);
		// printf("thread %d has seed %d \n", threadId, seed);
	}

}