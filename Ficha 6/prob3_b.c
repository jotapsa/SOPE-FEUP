// PROGRAMA p03.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

void *PrintHello(void *threadnum)
{
  printf("Hello from thread no. %d!\n", *(int *) threadnum);
  pthread_exit(NULL);
}

int main()
{
  pthread_t threads[NUM_THREADS];
  int arg[NUM_THREADS];

  for(int t=0; t< NUM_THREADS; t++){
    printf("Creating thread %d\n", t+1);
    arg[t] = t+1;
    pthread_create(&threads[t], NULL, PrintHello, (void *)&arg[t]);
  }

  pthread_exit(0);
}
