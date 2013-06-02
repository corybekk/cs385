#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
  
  double stime;
  double etime;
  int rank, size;
  int numberInCircle = 0;
  int tossPerProcess;
  int root = 0;
  int value;
  int totalHits = 0;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  srand((unsigned)time(0) + rank);
  MPI_Barrier(MPI_COMM_WORLD);

  if(rank == root)
    {
      printf("enter number of tosses:"); //idk why, but it skips this printf
      scanf("%d", &value);
      tossPerProcess = value/(size-1);//process 0 doesnt do calculations. so to test 1 process we have to put 2 
    }

  stime = MPI_Wtime();
    
  MPI_Bcast(&tossPerProcess, 1, MPI_INT, root, MPI_COMM_WORLD);
 
  if(rank != root)
    {
      printf("process %i recieved %i tosses\n", rank, tossPerProcess);
      double x,y, distance;
      int i;
      for(i= 0; i < tossPerProcess; i++)
	{
	  x = (rand()-RAND_MAX/2.0)/(RAND_MAX/2.0);
	  y = (rand()-RAND_MAX/2.0)/(RAND_MAX/2.0);
	  distance = x*x + y*y;
	  if(distance <= 1)
	    numberInCircle++;
	}
        printf("process %i made %i hits\n", rank, numberInCircle);
    }
  
  MPI_Reduce(&numberInCircle, &totalHits, 1, MPI_LONG_LONG, MPI_SUM, root, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);

  double ptime;
  etime = MPI_Wtime();
  MPI_Reduce(&etime, &ptime, 1, MPI_DOUBLE, MPI_MAX, root, MPI_COMM_WORLD);
  ptime = ptime - stime;
 
  if(rank == root)
    {
      printf("total hits: %i\n", totalHits);
      printf("Pi Equals: %f\n", (4.0 * totalHits)/value);
      printf("Max time across processes: %f\n", ptime);
    }
  
  MPI_Finalize();
  return 0;
}
