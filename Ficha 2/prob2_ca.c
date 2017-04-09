#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>

#define MAX_LEN 256

int main (int argc, char *argv[]){
  clock_t start, end;
  struct tms t;
  long ticks;
  int bytes;
  char copyBuffer[MAX_LEN];
  FILE *source, *dest;

  start = times(&t);    //Inicio da medicao
  ticks = sysconf(_SC_CLK_TCK);

  if (argc!=3){
    printf("Wrong number of arguments\n");
    exit(1);
  }

  source = fopen (argv[1], "r");
  dest = fopen (argv[2], "w");

  while ((bytes = fread(copyBuffer, 1, MAX_LEN, source))>0){ //copia mos um byte 256 vezes
    fwrite (copyBuffer, 1, bytes, dest);
  }

  fclose (source); fclose(dest);

  printf("\nClock ticks per second: %ld\n", ticks);

  end = times(&t);

  printf("Clock:  %4.2f s\n", (double)(end-start)/ticks);
  printf("User time:  %4.2f s\n", (double)t.tms_utime/ticks);
  printf("System time:  %4.2f s\n", (double)t.tms_stime/ticks);
  printf("Children user time:  %4.2f s\n", (double)t.tms_cutime/ticks);
  printf("Children system time:  %4.2f s\n", (double)t.tms_cstime/ticks);

  return 0;
}
