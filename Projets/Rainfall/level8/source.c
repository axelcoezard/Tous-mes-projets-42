//--------------------------------------------------//
//               LEVEL 8 SOURCE SCRIPT              //
//--------------------------------------------------//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>

int* auth;
char* service;

int main(void)
{
	// char cVar1;
	// char *pcVar2;
	// int iVar3;
	// uint uVar4;
	// byte *pbVar5;
	// byte *pbVar6;
	// bool bVar7;
	// undefined uVar8;
	// undefined uVar9;
	// bool bVar10;
	// undefined uVar11;
	// byte bVar12;
	// byte local_90 [5];
	// char local_8b [2];
	// char acStack_89 [125];

	char *input;
	char inputBuffer[128];
	char authString[32];

	// ----------------------------------------

	// bVar12 = 0;
	// do {
	// } while( true );

	while (true)
	{
		// printf("%p, %p \n",auth,service);
		// pcVar2 = fgets((char *)local_90,0x80,stdin);
		// bVar7 = false;
		// bVar10 = pcVar2 == (char *)0x0;
		// if (bVar10) {
		// 	return 0;
		// }

		printf("%p, %p \n", auth, service);
		input = fgets((char *)inputBuffer, 128, stdin); // 0x80 = 128 decimal
		if (input == NULL) {
			return EXIT_SUCCESS;
		}

		// ----------------------------------------

		// iVar3 = 5;
		// pbVar5 = local_90;
		// pbVar6 = (byte *)"auth ";
		// do {
		// 	if (iVar3 == 0) break;
		// 	iVar3 = iVar3 + -1;
		// 	bVar7 = *pbVar5 < *pbVar6;
		// 	bVar10 = *pbVar5 == *pbVar6;
		// 	pbVar5 = pbVar5 + (uint)bVar12 * -2 + 1;
		// 	pbVar6 = pbVar6 + (uint)bVar12 * -2 + 1;
		// } while (bVar10);
		// uVar8 = 0;
		// uVar11 = (!bVar7 && !bVar10) == bVar7;
		// if ((bool)uVar11) {
		// 	auth = (undefined4 *)malloc(4);
		// 	*auth = 0;
		// 	uVar4 = 0xffffffff;
		// 	pcVar2 = local_8b;
		// 	do {
		// 		if (uVar4 == 0) break;
		// 		uVar4 = uVar4 - 1;
		// 		cVar1 = *pcVar2;
		// 		pcVar2 = pcVar2 + (uint)bVar12 * -2 + 1;
		// 	} while (cVar1 != '\0');
		// 	uVar4 = ~uVar4 - 1;
		// 	uVar8 = uVar4 < 0x1e;
		// 	uVar11 = uVar4 == 0x1e;
		// 	if (uVar4 < 0x1f) {
		// 		strcpy((char *)auth,local_8b);
		// 	}
		// }

		if (strncmp(inputBuffer, "auth ", 5) == 0) {
			auth = (int *) malloc(4);
			*auth = 0;

			if (strlen(authString) < 30) {
				strcpy((char *) auth, authString);
			}
		}

		// ----------------------------------------

		// iVar3 = 5;
		// pbVar5 = local_90;
		// pbVar6 = (byte *)"reset";
		// do {
		// 	if (iVar3 == 0) break;
		// 	iVar3 = iVar3 + -1;
		// 	uVar8 = *pbVar5 < *pbVar6;
		// 	uVar11 = *pbVar5 == *pbVar6;
		// 	pbVar5 = pbVar5 + (uint)bVar12 * -2 + 1;
		// 	pbVar6 = pbVar6 + (uint)bVar12 * -2 + 1;
		// } while ((bool)uVar11);
		// uVar9 = 0;
		// uVar8 = (!(bool)uVar8 && !(bool)uVar11) == (bool)uVar8;
		// if ((bool)uVar8) {
		// 	free(auth);
		// }

		else if (strncmp(inputBuffer, "reset", 5) == 0) {
			free(auth);
		}

		// ----------------------------------------

		// iVar3 = 6;
		// pbVar5 = local_90;
		// pbVar6 = (byte *)"service";
		// do {
		// 	if (iVar3 == 0) break;
		// 	iVar3 = iVar3 + -1;
		// 	uVar9 = *pbVar5 < *pbVar6;
		// 	uVar8 = *pbVar5 == *pbVar6;
		// 	pbVar5 = pbVar5 + (uint)bVar12 * -2 + 1;
		// 	pbVar6 = pbVar6 + (uint)bVar12 * -2 + 1;
		// } while ((bool)uVar8);
		// uVar11 = 0;
		// uVar8 = (!(bool)uVar9 && !(bool)uVar8) == (bool)uVar9;
		// if ((bool)uVar8) {
		// 	uVar11 = (byte *)0xfffffff8 < local_90;
		// 	uVar8 = acStack_89 == (char *)0x0;
		// 	service = strdup(acStack_89);
		// }

		else if (strncmp(inputBuffer, "service", 7) == 0) {
			service = strdup(inputBuffer + 8);
		}

		// ----------------------------------------

		// iVar3 = 5;
		// pbVar5 = local_90;
		// pbVar6 = (byte *)"login";
		// do {
		// 	if (iVar3 == 0) break;
		// 	iVar3 = iVar3 + -1;
		// 	uVar11 = *pbVar5 < *pbVar6;
		// 	uVar8 = *pbVar5 == *pbVar6;
		// 	pbVar5 = pbVar5 + (uint)bVar12 * -2 + 1;
		// 	pbVar6 = pbVar6 + (uint)bVar12 * -2 + 1;
		// } while ((bool)uVar8);
		// if ((!(bool)uVar11 && !(bool)uVar8) == (bool)uVar11) {
		// 	if (auth[8] == 0) {
		// 		fwrite("Password:\n",1,10,stdout);
		// 	}
		// 	else {
		// 		system("/bin/sh");
		// 	}
		// }

		else if (strncmp(inputBuffer, "login", 5) == 0) {
			if ((int) service - (int) auth == 32) {
				system("/bin/sh");
			} else {
				fwrite("Password:\n", 1, 10, stdout);
			}
		}
	}
	return EXIT_SUCCESS;
}
