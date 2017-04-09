#include <stdio.h> //getchar()
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
  int fd;
  char *text1="AAAAA";
  char *text2="BBBBB";
  fd = open("f1.txt",O_CREAT|O_EXCL|O_TRUNC|O_WRONLY|O_SYNC,0600); //Vai truncar ("resetar") o ficheiro f1.txt
  if (fd == -1){
    perror ("f1.txt");
    exit (1);
  }

  getchar ();
  write(fd,text1,5);
  getchar ();
  write(fd,text2,5);

  close(fd);
  return 0;
}
