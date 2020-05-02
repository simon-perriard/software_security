// Compile with `gcc -static -m32 -fno-stack-protector -O0 -s`
// the data/function sections trick removes unused functions, so that '/bin/sh' is not present in the binary :)

#include <stdio.h>
#include <unistd.h>
#include <string.h>

char command[60];

void param_change1(int a) {
  if (a == 60) {
    char* buff = "/bin/";
    strcat(command, buff);
  }
}

void param_change2(int b , int c) {
  if (b == 80 && c == 20) {
    char* buff = "sh";
    strcat(command, buff);
  }
}

void way_to_flag() {
  printf("Not that easy!\n");
  char* argv[] = { "/bin/date", NULL };
  execve("/bin/date", argv, NULL);
}

void bad_function(char* a) {
  char buffer[100];
  strcpy(buffer,a);
}

int main() {
  printf("I've upgraded my armor this time! Try me!\n");
  fflush(stdout);
  char input[1024];
  scanf("%1023[^\n]", input);
  bad_function(input);
  return 0;
}
