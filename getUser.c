#include "./headers.h"

void getUser(char *user) {
	uid_t uid = geteuid();
	struct passwd *pw = getpwuid(uid);
	if(pw) {
		strcpy(user, pw->pw_name);
	}
}

