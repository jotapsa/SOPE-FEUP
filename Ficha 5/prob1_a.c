#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main (){
  int a, b, fd[2];
  pid_t pid;
  int status;

  if (pipe(fd)==-1){
    fprintf (stderr, "Pipe error\n");
    exit (1);
  }

  pid = fork ();

  if (pid<0){
    fprintf (stderr, "Fork error\n");
    exit (2);
  }
  else if (pid >0){ //pai
    close (fd[0]); //fecha o lado recetor do Pipe
    printf ("Introduza dois numeros: ");
    scanf ("%d %d", &a, &b);

    write(fd[1], &a, sizeof(int));
    write(fd[1], &b, sizeof(int));

    waitpid (pid, &status, 0); //Espera pelo filho
  }
  else{
    close (fd[1]); //fecha o lado emissor do Pipe
    read (fd[0], &a, sizeof(int));
    read (fd[0], &b, sizeof(int));

    printf ("%d + %d = %d\n", a, b, a+b);
    //...
  }

  return 0;
}
