// PROGRAMA p01.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define STDERR 2
#define NUMITER 10000

int N=50000;

void * thrfunc(void *arg)
{
  int *written = (int *) malloc (sizeof(int));

  while (N >0 ) {
    printf ("%s", (char*) arg);
    *written= *written + 1;
    N--;
  }

  pthread_exit (written);
}
int main()
{
  pthread_t ta, tb;
  void *a, *b;

  pthread_create(&ta, NULL, thrfunc, "1");
  pthread_create(&tb, NULL, thrfunc, "2");

  pthread_join (ta, &a);
  pthread_join (tb, &b);


  printf ("\nA thread 1 escreveu %d caracteres\n", *(int*)a);
  printf ("A thread 2 escreveu %d caracteres\n",*(int *)b);

  return 0;
}
