//--------------------------------------------------//
//               LEVEL 2 SOURCE SCRIPT              //
//--------------------------------------------------//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int p(void)
{
	unsigned int unaff_retaddr;
	char local_50[76];

	fflush(stdout);
	gets(local_50);

	if ((unaff_retaddr & 0xb0000000) == 0xb0000000) {
		printf("(%p)\n", unaff_retaddr); /* WARNING: Subroutine does not return */
		return EXIT_FAILURE;
	}

	puts(local_50);
	strdup(local_50);

	return EXIT_SUCCESS;
}

int main(void)
{
	return p();
}
