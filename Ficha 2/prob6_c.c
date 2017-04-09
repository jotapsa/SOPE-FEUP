// PROGRAMA p6a.c ( referido na alínea a) )
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h> //chdir()

int main(int argc, char *argv[])
{
  DIR *dirp;
  struct dirent *direntp;
  struct stat stat_buf;
  char *str;

  if (argc != 2)
  {
    fprintf( stderr, "Usage: %s dir_name\n", argv[0]);
    exit(1);
  }

  if ((dirp = opendir( argv[1])) == NULL)
  {
    perror(argv[1]);
    exit(2);
  }

  chdir(argv[1]);

  while ((direntp = readdir( dirp)) != NULL)
  {
    if (stat(direntp->d_name, &stat_buf)==-1){  //Nao faco a minima pq crasha.. mas pode ter a ver com o facto que chamar stat no cwd vai devolver o cwd e por ai fora...
      perror (direntp->d_name);
      exit (1);
    }
    if (S_ISREG(stat_buf.st_mode)){
      str = (char*) malloc (sizeof(char)*256);
      sprintf (str,"regular\tSize(bytes): %lu", stat_buf.st_size);
    }
    else if (S_ISDIR(stat_buf.st_mode)) str = "directory";
    else str = "unknown";
    printf("%-25s - %s", direntp->d_name, str);
    printf("\t i-node correspondente: %lu\n", stat_buf.st_ino);

    free(str);
  }

  closedir(dirp);
  exit(0);
}
