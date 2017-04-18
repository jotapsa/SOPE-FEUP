// PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define STDERR 2
#define NUMITER 10000

void * thrfunc(void *arg)
{
  char *par = arg;

  fprintf(stderr, "Starting thread %c\n", *par);

  for (int i = 1; i <= NUMITER; i++) {
    write(STDERR,par,1);
  }

  return NULL;
}
int main()
{
  pthread_t ta, tb;
  char par = '1';

  pthread_create(&ta, NULL, thrfunc, &par);
  par +=1;
  pthread_create(&tb, NULL, thrfunc, &par);
  //Ao usar a mesma variavel para guardar o parametro das theads acontece que ao "atualizarmos" na funcao principal tambem
  //"atualizamos" nas threads, visto que manda mos a referencia

  pthread_join(ta, NULL);
  pthread_join(tb, NULL);

  return 0;
}
