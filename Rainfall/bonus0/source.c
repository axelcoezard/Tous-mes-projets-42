//--------------------------------------------------//
//               BONUS 0 SOURCE SCRIPT              //
//--------------------------------------------------//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>

void p(char inputBuffer, char ppBuffer) {
	char buffer[4104];

	// show our global buffer which is " - "
	puts(ppBuffer);

	// read stdin into buffer
	read(0, buffer, 4096); // 0x1000 = 4096

	// remove \n from buffer
	char* ptr = strchr(buffer, '\n'); // 10 is \n
	if (ptr != NULL) {
		*ptr = '\0';
	}

	// copy buffer into inputBuffer
	strncpy(inputBuffer, buffer, 20); // 0x14 = 20
}

void pp(char* myBuffer)
{
	char global_buffer[4096] = " - ";
	char input_1[20];
	char input_2[20];

	// call p() twice with input_1 and input_2
	p(input_1, &global_buffer);
	p(input_2, &global_buffer);

	// copy input_1 into myBuffer
	strcpy(myBuffer, input_1);

	// we removed everything inbetween because it was doing a strlen in the void

	// append a space to myBuffer
	myBuffer[strlen(myBuffer)] = 0x20; // 0x20 = space

	// append input_2 to myBuffer
	strcat(myBuffer, input_2);
	return;
}

int main(void) {
	char myBuffer[54];

	// call pp() with myBuffer
	pp(myBuffer);

	// show myBuffer
	puts(myBuffer);

	return EXIT_SUCCESS;
}
