//--------------------------------------------------//
//               BONUS 1 SOURCE SCRIPT              //
//--------------------------------------------------//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>

int main(int argc, char** argv)
{
	int uVar1;
	char buffer[40];

	int size = atoi(argv[1]);

	// notre 1er argument doit être un nombre inferieur à 10
	if (size < 10) {
		// on copie les (size * 4) octets de argv[2] dans buffer (buffer fait 40 octets)
		memcpy(buffer, argv[2], size * 4);
		if (size == 0x574f4c46) { // 1463249894 en decimal ou "WOLF" en ascii
			execl("/bin/sh","sh",0);
		}
		uVar1 = 0;
	} else {
		uVar1 = 1;
	}
	return uVar1;
}

