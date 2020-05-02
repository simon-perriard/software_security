// Yes, you could change this file, but you won't learn GDB that way, which you'll need for later!

#include <stdbool.h>
#include <stdio.h>

const char y1 = 'a';
const char y2 = 'b';
const char y3 = 'x';
const char y4 = 'y';
const char y5 = 'i';
const char y6 = 'j';

char x1 = 'f' ^ 'a';
char x2 = 'l' ^ 'b';
char x3 = 'a' ^ 'x';
char x4 = 'g' ^ 'y';
char x5 = 'y' ^ 'i';
char x6 = '-' ^ 'j';

int main() {
  bool c = false;
  if(c) { printf("The flag is: %c%c%c%c%c%c%c%c%c%c%c\n", x1 ^ y1, x2 ^ y2, x3 ^ y3, x4 ^ y4, x4 ^ y4, x5 ^ y5, x6 ^ y6, x1 ^ y1, x2 ^ y2, x3 ^ y3, x4 ^ y4); }
  return 0;
}
