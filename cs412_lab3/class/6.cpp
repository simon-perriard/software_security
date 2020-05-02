// Compile with `g++ -static -m32 -O0 -s`

#include <cstdio>
#include <cstdlib>
#include <csignal>
using namespace std;

void feedback() {
	char comment[500];
	printf("Do you have any comment about the class?\n");
	fflush(stdout);
	scanf("%500s", comment);
	printf("We appreciate your feedback.\n");
	fflush(stdout);
}

void grade() {
	int q1, grade;
	printf("Q1: is P == NP?\n");
	fflush(stdout);
	scanf("%d", q1);

	grade = rand();
	if (grade == 6) {
		printf("Congratulations, you passed the class!\n");
		fflush(stdout);
		system("cat flag");
	}

	printf("You should leave better comments next semester!\n");
	fflush(stdout);
}

int main() {
	srand(7);
	feedback();
	grade();
	return 0;
}
