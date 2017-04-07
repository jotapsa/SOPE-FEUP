#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>


int main ()
{
  pid_t pid;

  pid = fork ();

  if (pid>0) //pai
  {
    printf ("Hello ");
  }
  else if (pid == 0) // filho
  {
    pid = fork ();
    if (pid>0) //mesmo filho
    {
      printf ("my ");
    }
    else if (pid == 0) //neto
    {
      printf ("friend !\n");
    }
  }

  return 0;
}
