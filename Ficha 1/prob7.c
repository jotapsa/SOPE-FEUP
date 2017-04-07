#include <stdio.h>
#include <stdlib.h>

void handler1 (){
	printf ("Executing exit handler 1\n");
	exit(0); //Nao interessa que um dos handlers termine com exit, o programa vai chamar os restantes independentemente

}

void handler2 (){
	printf ("Executing exit handler 2\n");
}

int main ()
{

	/*A ordem pela qual os exit handlers sao chamados e' inversa da qual os "invocamos" na funcao main */

	atexit(handler2);
	atexit(handler1);
	atexit(handler1); //Podemos chamar o mesmo exit handler mais do que uma vez

	//abort (); //Aborted (core dumped) e nao chama nenhum exit handler

	printf ("Main done !\n");

	return 0;
}
