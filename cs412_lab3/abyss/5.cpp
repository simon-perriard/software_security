// Compile with `g++ -m32 -static -O0 -s`

#include <cstdio>

int main(){
	char abyss[10000];
	printf("when you gaze long into an abyss the abyss also gazes into you...\n");
	fflush(stdout);
	scanf("%10000s", abyss);
	printf(abyss);
	fflush(stdout);
	return 0;
}
