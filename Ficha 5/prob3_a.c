#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define N 6
#define BUFFER_SIZE 256

static int cmp(const void *p1, const void *p2){
    const char *lhs = p1;
    const char *rhs = p2;
    return strcmp((const char*)*lhs, (const char*)*rhs);
}

int main (int argc, char *argv[]){
  char *names[N], nameBuffer[BUFFER_SIZE];
  FILE *namesFile;
  unsigned int i=0;

  if (argc != 2){
    fprintf (stderr, "%s [ficheiro]", argv[0]);
    exit (1);
  }

  if ((namesFile = fopen (argv[1], "r")) ==NULL){
    perror (argv[1]);
    exit(2);
  }

  while (fgets(nameBuffer, BUFFER_SIZE, namesFile) != NULL){
    names[i++] = strdup(nameBuffer);
  }

  //qsort(names, N, BUFFER_SIZE, cmp);


  for (unsigned int j=0; j<N; j++){
    printf ("%s", names[j]);
    free(names[j]);
  }

  return 0;
}
