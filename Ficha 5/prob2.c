#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main (){
  int a, b, res, fd[2], resfd[2];
  pid_t pid;
  int status;

  if (pipe(fd)==-1 || pipe(resfd)==-1){
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
    close (resfd[1]); // fecha o lado emissor do Pipe com o resultado

    printf ("Introduza dois numeros: ");
    scanf ("%d %d", &a, &b);

    write(fd[1], &a, sizeof(int));
    write(fd[1], &b, sizeof(int));

    waitpid (pid, &status, 0); //Espera pelo filho

    read (resfd[0], &res, sizeof(int));

    printf ("%d + %d = %d\n", a, b, res);
  }
  else{
    close (fd[1]); //fecha o lado emissor do Pipe
    close (resfd[0]); //fecha o lado recetor do Pipe com o resultado
    read (fd[0], &a, sizeof(int));
    read (fd[0], &b, sizeof(int));

    res = a+b;

    write (resfd[1], &res, sizeof(int));
  }

  return 0;
}
