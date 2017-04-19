#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

void *sleepy(void *threadnum)
{
  pthread_t selfTid;

  sleep(1);
  selfTid = pthread_self ();
  printf ("Hello! I'm thread number %d and my tid is %lu\n", *(int*)threadnum, selfTid);

  pthread_exit (threadnum);
}

int main (){
  pthread_t threads[N];
  int arg[N];
  int *exitValue;

  for (unsigned int i=0; i<N; i++){
    arg[i] = i+1;
    pthread_create (&threads[i], NULL, sleepy, &arg[i]);
  }


  for (unsigned int i=0; i<N; i++){
    pthread_join(threads[i], (void **) &exitValue);-
    printf ("Thread number %d has ended\n", *(int *) exitValue);
  }
  //OU (ou ambos :) )
  pthread_exit (0);
}
