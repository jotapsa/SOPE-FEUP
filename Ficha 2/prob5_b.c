// PROGRAMA p5b.c
#include <stdio.h> //getchar()
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
int fd;
char *text1="CCCCC";
char *text2="DDDDD";
fd = open("f1.txt", O_WRONLY|O_SYNC,0600);
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
