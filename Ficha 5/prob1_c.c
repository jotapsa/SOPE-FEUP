#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

#define MAX_SIZE 10

int main (){
  int status, fd[2];
  char a[MAX_SIZE], b[MAX_SIZE];
  pid_t pid;
  int n;

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
    printf ("Introduza dois numeros, separados por ENTER\n");

    n = read (STDIN_FILENO, a, MAX_SIZE);
    write(fd[1], a, n);

    read (STDIN_FILENO, b, MAX_SIZE);
    write (fd[1], b, MAX_SIZE);

    waitpid (pid, &status, 0); //Espera pelo filho
  }
  else{
    close (fd[1]); //fecha o lado emissor do Pipe
    read (fd[0], a, MAX_SIZE);
    read (fd[0], b, MAX_SIZE);

    printf ("%d + %d = %d\n", atoi(a), atoi(b), atoi(a)+atoi(b));
    //...
  }

  return 0;
}
