//--------------------------------------------------//
//               LEVEL 7 SOURCE SCRIPT              //
//--------------------------------------------------//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

char c[68];

void m(void* param_1, int param_2, char param_3, int param_4, int param_5) {
	time_t tVar1;

	tVar1 = time(NULL); // (time_t *)0x0 = NULL
	printf("%s - %ld\n", c, (long) tVar1);
}

int main(int ac, char** argv)
{
	int* puVar1;
	void* pvVar2;
	int* puVar3;
	FILE* __stream;

	puVar1 = (int *) malloc(8);
	*puVar1 = 1;

	pvVar2 = malloc(8);
	puVar1[1] = pvVar2;

	puVar3 = (int *) malloc(8);
	*puVar3 = 2;

	pvVar2 = malloc(8);
	puVar3[1] = pvVar2;

	strcpy((char *) puVar1[1], argv[1]);
	strcpy((char *) puVar3[1], argv[2]);

	__stream = fopen("/home/user/level8/.pass","r");
	fgets(c, 68, __stream); // 0x44 = 68 decimal
	puts("~~");

	return EXIT_SUCCESS;
}
