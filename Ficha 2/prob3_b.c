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

  if (argc!=2 && argc != 3){
    printf("Wrong number of arguments\n");
    return 1;
  }

  source = open (argv[1], O_RDONLY);
  if (source == -1){
    perror (argv[1]);
    return 2;
  }

  if (argc == 3){
    dest = open (argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);

    if (dest == -1){
      perror (argv[2]);
      close (source);
      return 3;
    }

    //Identifica o ficheiro dest, com o descritor STDOUT_FILENO
    if (dup2 (dest, STDOUT_FILENO) == -1){
      perror ("Error");
      close (source);
      close (STDOUT_FILENO);
      exit(1);
    }
  }

  while ((bytes = read (source, copyBuffer, MAX_LEN))>0){
    if ((writtenBytes = write (STDOUT_FILENO, copyBuffer, bytes)) <= 0 || writtenBytes != bytes){
      perror (argv[2]);
      close (source);
      close (STDOUT_FILENO);
    }
  }

  close (source);
  close (STDOUT_FILENO);
  return 0;
}
