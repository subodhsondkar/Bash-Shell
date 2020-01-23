#include "./headers.h"

void getTermIndices(char argument[BUFFERSIZE], int *current_command) {
	int i = 1, j = 1, string_on = 0;
	if(argument[0] == ' ') {
		current_command[0] = 1;
	}
	else {
		current_command[0] = 0;
	}
	while(argument[i] != '\0') {
		if(argument[i] == '"' && string_on == 0) {
			string_on = 1;
		}
		else if(argument[i] == '"' && string_on == 1) {
			string_on = 0;
		}
		else if(argument[i] == ' ' && string_on == 0) {
			argument[i] = '\0';
			current_command[j] = i + 1;
			j++;
		}
		i++;
	}
}

