#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main ()
{
  pid_t pid;
  int status;
  pid = fork ();

  if (pid>0){ //pai
    wait (&status);
    printf ("world !\n");
  }
  else if (pid == 0){ //filho
    printf ("Hello ");
  }
  else{ //erro
    perror ("fork");
    return 1;
  }

  return 0;
}
