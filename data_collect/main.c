# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <math.h>

void seedThreads(unsigned int* seeds); //Generate unique seeds for each thread.
void computeSave(unsigned int* seeds);

int main()
{
	

	omp_set_num_threads(4);

	int nThreads = 4;

	//int id;

	unsigned int* seeds = (unsigned int*)malloc(sizeof(int)*nThreads);

	seedThreads(seeds);

	computeSave(seeds);
	
	//printf("The first seed is %d", seeds[0]);

//#	pragma omp parallel \
//	private(id) shared(seeds)
//	{
//		id = omp_get_thread_num();
//		printf("thread %d has seed %d \n", id, seeds[id]);
//	}



	return 0;
}

void seedThreads(unsigned int* seeds) 
{

#	pragma omp parallel
	{
		unsigned int threadId = omp_get_thread_num();

		unsigned int seed = (unsigned)time(NULL);

		seeds[threadId] = (seed & 0xFFFFFFF0) | (threadId + 1);
		// printf("thread %d has seed %d \n", threadId, seed);
	}

}

void computeSave(unsigned int* seeds)
{
	FILE *res;
	res = fopen("Data3.csv", "w+");

	int i;
	unsigned int seed;
	float x, y, d;

# pragma omp parallel\
  shared(seeds,res) private(i,seed,x,y,d)
	{
		seed = seeds[omp_get_thread_num()];
		srand(seed);

#		pragma omp for schedule(static)
		for (i = 0; i < 250000; i++) {
			x = (float)((rand() % 6000)/10.0-300);
			y = (float)((rand() % 6000)/10.0-300);
			d = sqrt(pow(x, 2) + pow(y, 2));

			# pragma omp critical
			  {
				  fprintf(res, "%.4f, %.4f, %.4f \n", x+300, y+300, d);
				  //printf("Thread %d : x-> %.4f, y-> %.4f, d->%.4f, seed-> %d\n", omp_get_thread_num(), x,y,d,seed);
			  }
		}
		fclose(res);
	}
}