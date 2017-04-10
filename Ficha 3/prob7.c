// PROGRAMA p7.c
#include <stdio.h>
#include <unistd.h> //servicos exec
#include <stdlib.h>

int main(int argc, char *argv[])
{
  char prog[20];

  sprintf(prog,"%s.c",argv[1]); //passamos por argumento o nome do ficheiro que queremos compilar
  execlp("gcc","gcc",prog,"-Wall","-o",argv[1],NULL); //gcc prog.c -Wall -o prog

  printf("Can't compile %s", argv[1]); //Os servicos exec nunca retorna caso tenham sucesso
  exit(1);
}
