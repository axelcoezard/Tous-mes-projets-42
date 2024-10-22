//--------------------------------------------------//
//               LEVEL 5 SOURCE SCRIPT              //
//--------------------------------------------------//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void o(void)
{
	system("/bin/sh");
	exit(EXIT_FAILURE);
}

void n(void)
{
	char local_20c[520];

	fgets(local_20c, 512, stdin); // 0x200 = 512 decimal
	printf(local_20c);

	exit(EXIT_FAILURE);
}

void main(void)
{
	n();
	return;
}
