#include "./headers.h"

int getArgumentCount(char *command) {
	int argument_count = 0, string_on = 0, acceptable_subcommand = 0;
	for(int i = 0; command[i] != '\0'; i++) {
		if(command[i] == '"' && string_on == 0) {
			string_on = 1;
		}
		else if(command[i] == '"' && string_on == 1) {
			string_on = 0;
		}
		else if(command[i] == ';' && string_on == 0 && acceptable_subcommand == 0) {
			*(command + i) = ' ';
		}
		else if(command[i] == ';' && string_on == 0 && acceptable_subcommand == 1) {
			argument_count++;
			acceptable_subcommand = 0;
		}
		else if(command[i] != ' ' && command[i] != ';') {
			acceptable_subcommand = 1;
		}
	}
	return argument_count;
}

