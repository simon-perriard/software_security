// Compile with `gcc -static -O0 -s`

#include <stdio.h>
#include <stdlib.h>

// this leaks memory but whatever, the program will exit quickly
char* read_flag(void) {
	FILE* f = fopen("flag", "r");
	char* flag = calloc(64, sizeof(char));
	fscanf(f, "%63s", flag);
	fclose(f);
	return flag;
}

int main() {
	char* flag = read_flag();
	
	printf("Flag: %p\n", flag);

	printf("What's your name? ");
        fflush(stdout);
	char name[64];
	scanf("%63s", name);
	printf("Hello, ");
	printf(name);
	printf(", how are you?\n");
	fflush(stdout);

	return 0;
}
