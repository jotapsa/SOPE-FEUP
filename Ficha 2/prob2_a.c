#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 256

int main (int argc, char *argv[]){

  int bytes;
  char copyBuffer[MAX_LEN];
  FILE *source, *dest;

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

  return 0;
}
