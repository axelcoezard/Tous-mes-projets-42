//--------------------------------------------------//
//               LEVEL 1 SOURCE SCRIPT              //
//--------------------------------------------------//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void run(void)
{
	fwrite("Good... Wait what?\n", 1, 19, stdout); // 0x13 = 19
	system("/bin/sh");
	return;
}

void main(void)
{
	char local_50[76];

	gets(local_50);
	return;
}
