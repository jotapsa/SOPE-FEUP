// PROGRAMA p8.c
#include <stdio.h>
#include <sys/types.h>
#include <wait.h> //waitpid
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[], char *envp[])
{
  pid_t pid;
  int status;

  char **arg = (char **) malloc (sizeof(char *)*4);
  arg[0] = "ls";
  arg[1] = "-laR";
  arg[2] = argv[1];
  arg[3] = NULL;

  if (argc != 2) {
    printf("usage: %s dirname\n",argv[0]);
    exit(1);
  }
  pid=fork();
  if (pid > 0){
    printf("My child is going to execute command "
    "\"ls -laR %s\"\n", argv[1]);

    waitpid (pid, &status, 0); // We want it to halt execution
    printf ("%d Exit code was: %d\n", pid, status);
  }
  else if (pid == 0){
    execvp("ls", arg);

    printf("Command not executed !\n");
    exit(1);
  }
  exit(0);
}
