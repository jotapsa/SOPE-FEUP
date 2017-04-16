#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

typedef struct{
  int a, b;
} values;

int main (){
  values val;
  int status, fd[2];
  pid_t pid;

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
    scanf ("%d %d", &val.a, &val.b);

    write(fd[1], &val, sizeof(values));

    waitpid (pid, &status, 0); //Espera pelo filho
  }
  else{
    close (fd[1]); //fecha o lado emissor do Pipe
    read (fd[0], &val, sizeof(values));

    printf ("%d + %d = %d\n", val.a, val.b, val.a+val.b);
    //...
  }

  return 0;
}
