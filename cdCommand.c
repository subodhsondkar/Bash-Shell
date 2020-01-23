#include "./headers.h"

void cdCommand(char* cwd, char *path, char *home, int *address_mode) {
	chdir(path);
	char new_cwd[BUFFERSIZE], temp_cwd[BUFFERSIZE];
	getcwd(new_cwd, sizeof(new_cwd));
	strcpy(temp_cwd, new_cwd);
	temp_cwd[strlen(home)] = '\0';
	if(strcmp(home, temp_cwd) == 0) {
		strcpy(cwd, new_cwd + strlen(home));
		*address_mode = 1;
	}
	else {
		strcpy(cwd, new_cwd);
		*address_mode = 0;
	}
}

