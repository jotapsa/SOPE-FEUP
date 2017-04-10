// PROGRAMA p6.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(void)
{
  pid_t childPid;
  int i, j, status;

  printf("I'm process %d. My parent is %d.\n", getpid(),getppid());

  for (i=1; i<=3; i++) {
    childPid = fork();

    if ( childPid < 0) {
      printf("fork error");

      exit(1);
    }
    else if (childPid == 0) {
      printf("I'm process %d. My parent is %d."
      "I'm going to work for 1 second ...\n", getpid(),getppid());

      sleep(1); // simulando o trabalho do filho

      printf("I'm process %d. My parent is %d."
      "I finished my work\n", getpid(),getppid());
    }
    else{ // simulando o trabalho do pai
      for (j=1; j<=5; j++) {
        waitpid (-1, &status, WNOHANG | WUNTRACED); //-1 -> Esperar por um filho qualquer
        //WNOHANG. nao bloqueia se o filho nao tiver disponivel,
        //WUNTRACED se o status do filho ainda nao tiver sido reportado e' agora
        sleep(1);
        printf("father working ...\n");
      }
    }
  }
  exit(0);
}
