#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc != 3){
		perror("Nao deu dois argumentos");
		exit(1);
	}

	for (int i=0; i<atoi(argv[2]); i++)
	{
		printf("Hello %s!\n", argv[1]);
	}

	return 0;
}
