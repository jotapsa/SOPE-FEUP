// PROGRAMA p2.c
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
  printf("1\n");//A stream do standard output e' guardada num buffer antes de ser impressa
  //podemos dar flush (imprimir) esse buffer por exemplo com o caracter newline \n
  if(fork() > 0) {
    printf("2");
    printf("3");
  } else {
    printf("4");
    printf("5");
  }
  printf("\n");
  return 0;
}
