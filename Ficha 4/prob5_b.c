#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

void sigchld_handler (int signo){
  int status;
  wait(&status);
}
/*Apesar do facto que sempre que o processo receber o signal
SIGCHLD, o respetivo handler ser chamado, pode acontecer que o program counter
ja se encontre desse handler, e sendo assim iremos ficar com alguns sinais 
por processar (porque o processo pensa que ja tamos a processar esses sinais) */

int main(void)
{
  pid_t pid;
  int i, n;
  struct sigaction act;

  //Ignorar o sinal SIGCHLD
  act.sa_handler = sigchld_handler;
  sigemptyset (&act.sa_mask);
  act.sa_flags = 0;
  sigaction (SIGCHLD, &act, NULL);

  for (i=1; i<=10; i++){ //Criar 3 processos filhos
    pid=fork();

    if (pid == 0){
      printf("CHILD no. %d (PID=%d) working ... \n",i,getpid());
      sleep(15);
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
