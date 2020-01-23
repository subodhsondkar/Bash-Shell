#include "./headers.h"

void separateArguments(char *command, char arguments[][BUFFERSIZE], int argument_count) {
	int i = 0, j = 0, k = 0, argument_number = 0;
	while(command[i] != '\0') {
		if(command[i] == ';') {
			while(j <= i) {
				if(command[j] == ' ' || command[j] == ';') {
					char distinguisher = command[j];
					command[j] = '\0';
					strcat(arguments[argument_number], command + k);
					if(distinguisher == ' ') {
						strcat(arguments[argument_number], " ");
					}
					while((command[j] == ' ' || command[j] == '\0') && j <= i) {
						j++;
					}
					k = j;
					j--;
				}
				j++;
			}
			argument_number++;
		}
		i++;
	}
}

