// PROGRAMA p04a.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>


int main(void)
{
  pid_t pid;
  int i, n, status;
  struct sigaction act;

  //Ignorar o sinal SIGCHLD
  act.sa_handler = SIG_IGN;
  sigemptyset (&act.sa_mask);
  act.sa_flags = 0;
  sigaction (SIGCHLD, &act, NULL);

  for (i=1; i<=3; i++){ //Criar 3 processos filhos
    pid=fork();

    if (pid == 0){
      printf("CHILD no. %d (PID=%d) working ... \n",i,getpid());
      sleep(i*7); // child working ...
      printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());

      exit(0);
    }
  }

  for (i=1 ;i<=4; i++ ){
    printf("PARENT: working hard (task no. %d) ...\n",i);
    n=20; while((n=sleep(n))!=0);
    printf("PARENT: end of task no. %d\n",i);
  }

  exit(0);
}
/*The interrupt character (^C by default) sends SIGINT to every process in the terminal's foreground process group*/
