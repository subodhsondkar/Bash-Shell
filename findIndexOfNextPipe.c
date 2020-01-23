#include "./headers.h"

int findIndexOfNextPipe(char *argument, int k) {
	while(*(argument + k) != '|') {
		k++;
	}
	return k;
}
