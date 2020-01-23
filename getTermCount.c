#include "./headers.h"

int getTermCount(char *argument) {
	int i = 1, term_count = 1, string_on = 0;
	while(argument[i] != '\0') {
		if(argument[i] == '"' && string_on == 0) {
			string_on = 1;
		}
		else if(argument[i] == '"' && string_on == 1) {
			string_on = 0;
		}
		else if(argument[i] == ' ' && string_on == 0) {
			term_count++;
		}
		i++;
	}
	return term_count - 1;
}

