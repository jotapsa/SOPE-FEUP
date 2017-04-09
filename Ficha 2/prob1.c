#include <unistd.h> //STDIN_FILENO , STDOUT_FILENO e STDERR_FILENO
#include <termios.h>
#include <string.h>


/* A consola tem 3 componentes, conhecidos por standard input
(teclado), standard output (écran) e standard error (também écran) que são represen-
tados por ficheiros com os descritores 0, 1 e 2, a que correspondem as constantes
STDIN_FILENO , STDOUT_FILENO e STDERR_FILENO , definidas em <unistd.h> .*/

#define MAX_PASSWD_LEN 20

int main (){

  struct termios term, oldTerm;
  char pw[MAX_PASSWD_LEN+1], ch, asterisk ='*';
  unsigned int i;

  tcgetattr(STDIN_FILENO, &oldTerm); //Get the current console config
  term = oldTerm;
  term.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);

  write (STDOUT_FILENO, "\nPassword?", 11);

  for (i=0; i<MAX_PASSWD_LEN && read(STDIN_FILENO, &ch, 1) && ch!='\n'; i++){
    pw[i]=ch;
    write(STDOUT_FILENO, &asterisk, 1);
  }
  pw[i]=0; //terminating character

  tcsetattr(STDIN_FILENO, TCSANOW, &oldTerm);

  write(STDOUT_FILENO, "\n\nPassword: ", 12);
  write(STDOUT_FILENO, pw, strlen(pw));
  write(STDOUT_FILENO, "\n", 1);

  return 0;
}
