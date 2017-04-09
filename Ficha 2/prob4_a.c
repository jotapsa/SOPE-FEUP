#include <stdlib.h> //exit;
#include <stdio.h> //perror
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> //write and read


#define MAXSIZE 20
#define BUFFERSIZE 256

int main (){

  char destName[MAXSIZE], line[BUFFERSIZE];
  int dest, bytes, writtenBytes;

  write(STDOUT_FILENO, "Nome Ficheiro (Carregar no Enter):", 34);

  if ((bytes = read(STDIN_FILENO, destName, MAXSIZE)) == -1){
    perror ("Error");
    exit (1);
  }
  destName[bytes-1] = '\0'; // Se lemos 20 bytes (inclusive newline) queremos substituir o newline pelo car terminador

  dest = open (destName, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if (dest == -1){
    perror (destName);
    exit (2);
  }

  while ((bytes = read(STDIN_FILENO, line, BUFFERSIZE))>0){
    if ((writtenBytes = write (dest, line, bytes))<=0 || writtenBytes != bytes){
      perror (destName);
      close (dest);
      exit (3);
    }
  }


  close (dest);
  return 0;
}
