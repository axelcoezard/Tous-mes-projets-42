//--------------------------------------------------//
//               LEVEL 4 SOURCE SCRIPT              //
//--------------------------------------------------//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void p(char *param_1)
{
	printf(param_1);
}

int n(void)
{
	int m;
	char local_20c[520];

	fgets(local_20c, 512, stdin); // 0x200 = 512
	p(local_20c);
	if (m == 16930116) { // 0x1025544 = 16930116
		system("/bin/cat /home/user/level5/.pass");
	}
	return EXIT_SUCCESS;
}

void main(void)
{
	return n();
}
