// Compile with `gcc -static -m32 -fno-stack-protector -O0 -s`

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bad_function(char* str) {
    char buffer[100];
    strcpy(buffer, str);
}

void print_flag(int a) {
    if (a == 13) {
        printf("Nice job!\n");
        fflush(stdout);
        system("cat flag");
    } else {
        printf("Try again!\n");
        fflush(stdout);
    }
}

int main() {
    printf("Try attacking me!\n");
    fflush(stdout);
    char input[1024];
    scanf("%1023[^\n]", input);
    bad_function(input);
    return 0;
}
