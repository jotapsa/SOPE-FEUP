#include <stdio.h>
#include <stdlib.h> // srand, rand
#include <time.h> // time()
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static int flag=1;

void update_v (int *v)
{
	if (flag)
		*v = *v+1;
	else
		*v = *v-1;
}

void sigusr_handler(int signo)
{
	if (signo == SIGUSR1)
	{
		flag = 1;
	}
	else //SIGUSR2
	{
		flag = 0;
	}
}

void sigint_handler(int signo)
{
	printf("Entering SIGINT handler ...\n");
	sleep(1);
	printf("Exiting SIGINT handler ...\n");
}

int main ()
{
	int v=0;
	pid_t pid;
	time_t t;
	struct sigaction action_int, action_usr;

	/* Intializes random number generator */
	srand((unsigned) time(&t));

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

	if (sigaction (SIGUSR1, &action_usr, NULL) < 0 || sigaction (SIGUSR2, &action_usr, NULL) <0)
	{
		fprintf(stderr, "Unable to install SIGUSR1 or SIGUSR2 handler\n");
		exit(1);
	}

	pid = fork ();
	switch (pid){
		case -1:
			perror ("Fork failed");
			exit (1);
			break;
		case 0:
			while(1){
				printf ("%d\n", v);
				update_v (&v);
				sleep(2); //wakes up if recieves signal)
			}
			break;
		default:
			for (int i=0; i<50; i++){
				sleep(1);
				if (rand()%2 ==0){
					kill (pid, SIGUSR1);
				}
				else{
					kill (pid, SIGUSR2);
				}
			}
			kill (pid, SIGTERM);
			break;
	}

	return 0;
}
