// PROGRAMA p6a.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strerror()
#include <errno.h> //perror()

#define BUF_LENGTH 256

int main(int argc, char *argv[])
{
  if (argc != 3){
    printf ("usage: nome_do_executável file1 file2\n");
    return 0;
  }

  FILE *src, *dst;
  char buf[BUF_LENGTH];

  if ( ( src = fopen( argv[1], "r" ) ) == NULL ){
    perror("Error");
    exit(1);
  }
  if ( ( dst = fopen( argv[2], "w" ) ) == NULL ){
    printf("Error: %s\n", strerror(errno));
    exit(2);
  }
  while( ( fgets( buf, BUF_LENGTH, src ) ) != NULL ){
    fputs( buf, dst );
  }

  fclose( src );
  fclose( dst );

  exit(0); // zero é geralmente indicativo de "sucesso"
}
