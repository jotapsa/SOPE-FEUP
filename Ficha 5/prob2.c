#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

typedef enum {INT, FLOAT, INV} dataType_t;

typedef struct{
  dataType_t type;
  int resSum, resDif, resMult, resDivInt;
  float resDivFloat;
} results_t;

typedef struct{
  int a, b;
} input_t;

int main (){
  int fd[2], resfd[2];
  pid_t pid;
  int status;
  input_t input;
  results_t results;

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
    scanf ("%d %d", &input.a, &input.b);

    write(fd[1], &input, sizeof(input_t));

    waitpid (pid, &status, 0); //Espera pelo filho

    read (resfd[0], &results, sizeof(results_t));

    printf ("%d + %d = %d\n", input.a, input.b, results.resSum);
    printf ("%d - %d = %d\n", input.a, input.b, results.resDif);
    printf ("%d * %d = %d\n", input.a, input.b, results.resMult);
    if (results.type != INV){
      printf ("%d / %d = ",input.a, input.b);
      if (results.type == INT){
        printf ("%d\n", results.resDivInt);
      }
      else {
        printf ("%f\n", results.resDivFloat);
      }
    }
  }

  else{
    close (fd[1]); //fecha o lado emissor do Pipe
    close (resfd[0]); //fecha o lado recetor do Pipe com o resultado

    read (fd[0], &input, sizeof(input_t));
    results.resSum = input.a + input.b;
    results.resDif = input.a - input.b;
    results.resMult = input.a * input.b;
    if (input.b == 0){
      results.type = INV;
    }
    else if (input.a % input.b == 0){
      results.type = INT;
      results.resDivInt = input.a/input.b;
    }
    else{
      results.type = FLOAT;
      results.resDivFloat = (float) input.a/input.b;
    }

    write (resfd[1], &results, sizeof(results_t));
  }

  return 0;
}
