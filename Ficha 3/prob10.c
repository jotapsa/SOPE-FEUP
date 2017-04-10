// PROGRAMA p8.c
#include <stdio.h>
#include <sys/types.h>
#include <wait.h> //waitpid
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

void pr_exit(int status) //copiado do pdf
{
  if (WIFEXITED(status))
  printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
  else if (WIFSIGNALED(status))
  printf("abnormal termination, signal number = %d%s\n",
  WTERMSIG(status),
  #ifdef WCOREDUMP
  /* nem sempre está definida em sys/wait.h */
  WCOREDUMP(status) ? " (core file generated)" : "");
  #else
  "");
  #endif
  else if (WIFSTOPPED(status))
  printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}


int main(int argc, char *argv[], char *envp[])
{
  pid_t pid;
  int status;

  char **arg = (char **) malloc (sizeof(char *)*4);
  arg[0] = "ls";
  arg[1] = "-laR";
  arg[2] = argv[1];
  arg[3] = NULL;

  if (argc != 2 && argc != 3) {
    printf("usage: %s dirname [output dir]\n",argv[0]);
    exit(1);
  }
  if (argc == 3){
    int output;

    output = open (argv[2], O_WRONLY | O_CREAT | O_TRUNC | O_SYNC, S_IRUSR | S_IWUSR);
    dup2 (output, STDOUT_FILENO);
  }

  pid=fork();
  if (pid > 0){
    printf("My child is going to execute command "
    "\"ls -laR %s\"\n", argv[1]);

    waitpid (pid, &status, 0); // We want it to halt execution
    printf ("%d Exit code was: %d\n", pid, status);
    pr_exit(status);

  }
  else if (pid == 0){
    execvp("ls", arg);

    printf("Command not executed !\n");
    exit(1);
  }
  exit(0);
}
