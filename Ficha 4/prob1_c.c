// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void sigint_handler(int signo)
{
  printf("In SIGINT handler ...\n");
}

int main(void)
{

  struct sigaction act;

  act.sa_handler = sigint_handler; //signal handler
  sigemptyset(&act.sa_mask);  //initialize and empty a signal set so we dont block any signals when executing the handler
  act.sa_flags = 0; //aditional behaviors

  if (sigaction(SIGINT, &act, NULL) < 0)
  {
    fprintf(stderr,"Unable to install SIGINT handler\n");
    exit(1);
  }
  printf("Sleeping for 30 seconds ...\n");
  
  for (int i=0; i<30; i++)
    sleep(1);

  printf("Waking up ...\n");
  exit(0);
}
