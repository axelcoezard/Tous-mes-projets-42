//--------------------------------------------------//
//               BONUS 2 SOURCE SCRIPT              //
//--------------------------------------------------//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>

int language = 0;

int greetuser()
{
	unsigned char hello[30];
	unsigned char local_var;

	if (language == 1) {
		hello[0] = 'H';
		hello[1] = 'y';
		hello[2] = 'v';
		hello[3] = '\xc3'; // -0x3d + 256
		hello[4] = '\xa4'; // -0x5c + 256 = 0xa4
		hello[5] = '\xc3'; // -0x3d + 256 = 0xc3
		hello[6] = '\xa4'; // -0x5c + 256 = 0xa4
		hello[7] = ' ';
		hello[8] = 'p';
		hello[9] = '\xc3'; // -0x3d + 256 = 0xc3
		hello[10] = '\xa4'; // -0x5c + 256 = 0xa4
		hello[11] = 'i';
		hello[12] = 'v';
		hello[13] = '\xc3'; // -0x3d + 256
		hello[14] = '\xa4'; // -0x5c + 256 = 0xa4
		hello[15] = '\xc3'; // -0x3d + 256 = 0xc3
		hello[16] = '\xa4'; // -0x5c + 256 = 0xa4
		hello[17] = '\0';
	} else if (language == 2) {
		hello[0] = 'G';
		hello[1] = 'o';
		hello[2] = 'e';
		hello[3] = 'd';
		hello[4] = 'e';
		hello[5] = 'm';
		hello[6] = 'i';
		hello[7] = 'd';
		hello[8] = 'd';
		hello[9] = 'a';
		hello[10] = 'g';
		hello[11] = '!';
		hello[12] = '\0';
		//local_40 = CONCAT22(local_40._2_2_,0x20); // ???
	} else if (language == 0) {
		hello[0] = 'H';
		hello[1] = 'e';
		hello[2] = 'l';
		hello[3] = 'l';
		hello[4] = 'o';
		hello[5] = '\0';
	}

	strcat(hello, (char*) &local_var);
	puts(hello);
	return EXIT_SUCCESS;
}

int main(int ac, char *argv)
{
	char* env_lang;
	int buffer[10];
	char buffer_copy[36];

	if (ac == 3) {
		memset(buffer, 0, sizeof(buffer)); // ou un bzero

		strncpy(buffer, argv[1], 40); // 0x28 = 40
		strncpy(buffer_copy, argv[2], 32); // 0x20 = 32

		env_lang = getenv("LANG");
		if (env_lang != NULL) // (char)0x0 = NULL
		{
			if (memcmp(env_lang, "nl", 2) == 0) {
				language = 1;
			}
			else if (memcmp(env_lang, "fi", 2) == 0) {
				language = 2;
			}
		}

		memcpy(buffer_copy, buffer, 19);
		return greetuser();
	}
	return EXIT_FAILURE;
}
