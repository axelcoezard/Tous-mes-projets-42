//--------------------------------------------------//
//               LEVEL 6 SOURCE SCRIPT              //
//--------------------------------------------------//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

// fonction o qui affiche le contenu de .pass du level7
void n(void)
{
	system("/bin/cat /home/user/level7/.pass");
	return;
}

// fonction m qui affiche juste "Nope"
void m(void *param_1,int param_2,char *param_3,int param_4,int param_5)
{
	puts("Nope");
	return;
}

void main(int argc, char** argv)
{
	char *__dest;
	void **ppcVar1;

	__dest = (char *) malloc(64); // 0x40 = 64 decimal
	ppcVar1 = (void**) malloc(4); // 0x4 = 4 decimal
	*ppcVar1 = m;
	strcpy(__dest, argv[1]);
	void (**ppcVar1)();
	return;
}
