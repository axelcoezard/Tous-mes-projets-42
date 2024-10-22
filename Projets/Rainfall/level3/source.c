//--------------------------------------------------//
//               LEVEL 3 SOURCE SCRIPT              //
//--------------------------------------------------//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

char m;

int v(void)
{
	int m;
	char local_20c[520];

	// contrairement a gets, fgets est protégé contre les buffer overflow
	fgets(local_20c, 512, stdin); // 0x200 = 512
	printf(local_20c);

	// m est a l'adress 0x804988c
	if (m == 64) { // 0x40 = 64
		fwrite("Wait what?!\n", 1, 12, stdout); //oxc = 12
		system("/bin/sh");
	}
	return EXIT_SUCCESS;
}

void main(void)
{
	return v();
}
