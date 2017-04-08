#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sys/times.h>
#include <unistd.h>

int main (int argc, char *argv[ ]){
  clock_t start, end;
  struct tms t;
  long ticks;

  long tmp;
  time_t srandTime;

  start = times(&t);    //Inicio da medicao
  ticks = sysconf(_SC_CLK_TCK);

  /* Intializes random number generator */
  srand((unsigned) time(&srandTime));

  for (unsigned int i; tmp!= atol(argv[2]); i++){
    tmp = rand ()%atoi(argv[1]);
    printf ("%d: %ld\n", i, tmp);
  }

  //getchar ();

  printf("\nClock ticks per second: %ld\n", ticks);

  end = times(&t);

  printf("Clock:  %4.2f s\n", (double)(end-start)/ticks);
  printf("User time:  %4.2f s\n", (double)t.tms_utime/ticks);
  printf("System time:  %4.2f s\n", (double)t.tms_stime/ticks);
  printf("Children user time:  %4.2f s\n", (double)t.tms_cutime/ticks);
  printf("Children system time:  %4.2f s\n", (double)t.tms_cstime/ticks);

  return 0;
}
