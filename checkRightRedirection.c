#include "./headers.h"

int checkRightRedirection(char *argument) {
	int i = 0, string_on = 0;
	while(argument[i] != '\0') {
		if(argument[i] == '"' && string_on == 0) {
			string_on = 1;
		}
		else if(argument[i] == '"' && string_on == 1) {
			string_on = 0;
		}
		else if(argument[i] == '>' && string_on == 0) {
			if(argument[i + 1] == '>') {
				return 2;
			}
			return 1;
		}
		i++;
	}
	return 0;
}
