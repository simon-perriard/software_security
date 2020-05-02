// Compile with `gcc -static -O0 -s`

#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("...the secret...is...\n");
  fflush(stdout);
  system("cat flag");
  return 0;
}
