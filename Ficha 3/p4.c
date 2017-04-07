#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main ()
{
  pid_t pid;
  //int status;
  pid = fork ();

  if (pid>0){ //pai
    sleep (1);
    printf ("world !\n");
  }
  else if (pid == 0){ //filho
    printf ("Hello ");
  }
  else{ //erro

  }
}
