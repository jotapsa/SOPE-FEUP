#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> //read write
#include <stdlib.h> //exit;
#include <stdio.h>

#define MAX_LEN 256

int main (int argc, char *argv[]){

  int source, dest, bytes, writtenBytes;
  char copyBuffer[MAX_LEN];

  if (argc!=3){
    printf("Wrong number of arguments\n");
    return 1;
  }

  source = open (argv[1], O_RDONLY);
  if (source == -1){
    perror (argv[1]);
    return 2;
  }
  dest = open (argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR|S_IWUSR);
  if (dest == -1){
    perror (argv[2]);
    close (source);
    return 2;
  }

  while ((bytes = read (source, copyBuffer, MAX_LEN))>0){
    if ((writtenBytes = write (dest, copyBuffer, bytes)) <= 0 || writtenBytes != bytes){
      perror (argv[2]);
      close (source);  close (dest);
    }
  }

  close (source); close (dest);
  return 0;
}
