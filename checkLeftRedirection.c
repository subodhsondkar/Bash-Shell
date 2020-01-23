#include "./headers.h"

int checkLeftRedirection(char *argument, int k, int l) {
	int i = k, string_on = 0;
	while(argument[i] != '\0' && i < l) {
		if(argument[i] == '"' && string_on == 0) {
			string_on = 1;
		}
		else if(argument[i] == '"' && string_on == 1) {
			string_on = 0;
		}
		else if(argument[i] == '<' && string_on == 0) {
			return i;
		}
		i++;
	}
	return -1;
}
