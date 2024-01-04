//--------------------------------------------------//
//               LEVEL 0 SOURCE SCRIPT              //
//--------------------------------------------------//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
	int		iVarl;
	char*	local_20;
	int		local_1c;
	uid_t	local_18;
	gid_t	local_14;

	iVarl = atoi(argv[1]);
	if (iVarl == 423) {
		local_20 = strdup("/bin/sh");
		local_1c = 0;
		local_14 = getegid();
		local_18 = geteuid();
		setresgid(local_14, local_14, local_14);
		setresuid(local_18, local_18, local_18);
		execv("/bin/sh", &local_20);
	} else {
		fwrite("No !\n", 1, 5, stderr);
	}
	return 0;
}
