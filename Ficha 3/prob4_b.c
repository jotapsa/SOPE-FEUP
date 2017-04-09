#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>


int main () //Nao ha uma maneira correta de fazer com que o processo filho espere pelo processo pai
{
  pid_t pid;

  pid = fork ();

  if (pid>0){ //pai
    printf ("Hello ");
    fflush(stdout); // flush stdout
    //fflush(NULL); // flush everything
    sleep (2);
  }
  else if (pid == 0){ //filho
    sleep (1);
    printf ("world !\n");
  }
  else{ //erro
    perror ("fork");
    return 1;
  }

  return 0;
}
