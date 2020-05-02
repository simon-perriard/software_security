// Compile with: gcc -s -O0 -fsanitize=address
#include <stdio.h>
#include <stdlib.h>

struct state {
  char buffer[10];
  char command[100];
};

int main() {
  // no buffering, avoids the need for fflush all the time
  setvbuf(stdout, NULL, _IONBF, 0);

  struct state s;

  // A totally innocent command that will not allow you to get the flag
  // ASan will surely protect it
  s.command[0] = 'l';
  s.command[1] = 's';
  s.command[2] = '\0';

  printf("Hi! What's your name? ");
  scanf("%s", s.buffer);
  system(s.command);

  return 0;
}
