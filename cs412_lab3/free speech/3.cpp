// Compile with  `g++ -static -m32 -fno-stack-protector -O0 -s`

#include <cstdio>
#include <cstdlib>
#include <csignal>
using namespace std;

void flag() {
	printf("Nice!\n");
	fflush(stdout);
	system("cat flag");
}

int main() {
	char str[5000];
	printf("What do you want to say?\n");
	fflush(stdout);
	scanf("%s", str);
	printf(str);
	fflush(stdout);
	return 0;
}
