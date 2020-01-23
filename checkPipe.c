#include "./headers.h"

int checkPipe(char *argument) {
	int i = 0, string_on = 0, pipe_number = 0;
	while(argument[i] != '\0') {
		if(argument[i] == '"' && string_on == 0) {
			string_on = 1;
		}
		else if(argument[i] == '"' && string_on == 1) {
			string_on = 0;
		}
		else if(argument[i] == '|' && string_on == 0) {
			pipe_number++;
		}
		i++;
	}
	return pipe_number;
}
