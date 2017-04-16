
// PROGRAMA p04a.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>


int main(void)
{
  pid_t pid;
  int i, n, status;

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
    n=20; while((n=sleep(n))!=0); //Somos obrigados a esperar pelo fim desta operacao para libertar um filho
    printf("PARENT: end of task no. %d\n",i);

    printf("PARENT: waiting for child no. %d ...\n",i);
    pid=wait(&status);  //E' libertado do estado zombie apenas um filho de cada vez
    if (pid != -1)
    printf("PARENT: child with PID=%d terminated "\
    "with exit code %d\n",pid,WEXITSTATUS(status));
  }
  exit(0);
}