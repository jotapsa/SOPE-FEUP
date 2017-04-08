#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main (int argc, char *argv[ ]){
  long tmp;
  time_t t;

  /* Intializes random number generator */
  srand((unsigned) time(&t));

  for (unsigned int i; tmp!= atol(argv[2]); i++){
    tmp = rand ()%atoi(argv[1]);
    printf ("%d: %ld\n", i, tmp);
  }

  return 0;
}
