#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


void update_v (int flag, int *v)
{
	if (flag)
		*v = *v+1;
	else
		*v = *v-1;
}

void sigint_handler(int signo)
{
	if (signo == SIGUSR1)
	{

	}
	else //SIGUSR2
	{

	}
}

void sigusr_handler(int signo)
{
	printf("Entering SIG handler ...\n");
	printf("Exiting SIGINT handler ...\n");
}

int main ()
{
	struct sigaction action_int, action_usr;

	action_int.sa_handler = sigint_handler;
	sigemptyset(&action_int.sa_mask);
	action_int.sa_flags = 0;

	if (sigaction(SIGINT,&action_int,NULL) < 0)
	{
		fprintf(stderr,"Unable to install SIGINT handler\n");
		exit(1);
	}

	action_usr.sa_handler = sigusr_handler;
	sigemptyset(&action_int.sa_mask);
	action_int.sa_flags = 0;

	if (sigaction (SIGUSR1, &action_usr, NULL) < 0 || sigaction (SIGUSR1, &action_usr, NULL) <0)
	{
		fprintf(stderr, "Unable to install SIGUSR1 or SIGUSR2 handler\n");
		exit(1);
	}





}