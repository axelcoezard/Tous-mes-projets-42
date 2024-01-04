//--------------------------------------------------//
//               BONUS 3 SOURCE SCRIPT              //
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
	FILE *fileBuffer;
	char buffer_1[16];
	char buffer_2[66];

	// on ouvre le fichier .pass en lecture seule
	fileBuffer = fopen("/home/user/end/.pass","r");
	if ((fileBuffer == NULL) || (argc != 2))
	{
		return EXIT_FAILURE;
	}

	// on lit les 66 premiers octets du fichier .pass et on les stocke dans buffer_1
	bzero(buffer_1, 33);
	fread(buffer_1, 1, 66, fileBuffer); //0x42 = 66

	// on lit les 65 octets suivants du fichier .pass et on les stocke dans buffer_2
	fread(buffer_2, 1, 65, fileBuffer); // 0x41 = 65

	// on ferme le fichier .pass
	fclose(fileBuffer);

	// on remplace le (argv[1] / 4) eme octet de buffer_1 par \0
	buffer_1[atoi(argv[1]) / 4] = 0;

	// si le contenu de buffer_1 est égal à argv[1], on exécute /bin/sh
	// sinon on affiche le contenu de buffer_2
	if (strcmp(buffer_1, argv[1]) == 0) {
		execl("/bin/sh","sh", 0);
	} else {
		puts(buffer_2);
	}
	return EXIT_SUCCESS;
}
