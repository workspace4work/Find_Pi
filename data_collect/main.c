# include <stdio.h>
# include <stdlib.h>
# include <omp.h>
# include <math.h>

void seedThreads(unsigned int* seedsX, unsigned int* seedsY); //Generate unique seeds for each thread.
void computeSave(unsigned int* seedsX, unsigned int* seedsY);

int main()
{
	

	omp_set_num_threads(4);

	int nThreads = 4;

	//int id;

	unsigned int* seedsX = (unsigned int*)malloc(sizeof(int)*nThreads);
	unsigned int* seedsY = (unsigned int*)malloc(sizeof(int)*nThreads);

	seedThreads(seedsX, seedsY);
	
	//printf("The first seed is %d", seeds[0]);

//#	pragma omp parallel \
//	private(id) shared(seeds)
//	{
//		id = omp_get_thread_num();
//		printf("thread %d has seed %d \n", id, seeds[id]);
//	}



	return 0;
}

void seedThreads(unsigned int* seedsX, unsigned int* seedsY) {

#	pragma omp parallel
	{
		unsigned int threadId = omp_get_thread_num();

		unsigned int seed = (unsigned)time(NULL);

		seedsX[threadId] = (seed & 0xFFFFFFF0) | (threadId + 1);
		seedsY[threadId] = (seed & 0xFFF0F0F0) | (threadId + 1);
		// printf("thread %d has seed %d \n", threadId, seed);
	}

}

void computeSave(unsigned int* seedsX, unsigned int* seedsY)
{
	FILE *res;
	res = fopen("Data1.csv", "w+");

	int i;
	unsigned int seedX, seedY;
	float x, y, d;

# pragma omp parallel \
  shared(res) private(i,seedX, seedY,x,y,d)
  {
    seedX=seedsX[omp_get_thread_num()];
	seedY=seedsY[omp_get_thread_num()];
    
	#pragma omp for schedule(static)
    for(i = 0; i < 100000; i++){
	  srand(seedX);
      x = (float) (rand_r(&seedX) % 300);
	  srand(seedY);
	  y = (float) (rand_r(&seedY) % 300);
	  d = sqrt(pow(x,2)+pow(y,2));
	
	# pragma omp critical
	  fprintf(res, "%.4f, %.4f, %.4f \n", x,y,d);
      
      
      // printf("Thread %d: %c for seed %d\n", omp_get_thread_num(), res[i], i);
      
    }
  }
  fclose(res);
}