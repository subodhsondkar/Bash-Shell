void getUser(char *user);
int getArgumentCount(char *command);
void separateArguments(char *command, char arguments[][BUFFERSIZE], int argument_count);
int getTermCount(char *argument);
void getTermIndices(char argument[BUFFERSIZE], int *current_command);
void cdCommand(char* cwd, char *path, char *home, int *address_mode);
int lsCommand(char *path, int a_flag, int l_flag);
void pinfoCommand(pid_t pid);
int checkPipe(char *argument);
int checkLeftRedirection(char *argument, int k, int l);
int checkRightRedirection(char *argument);
int findIndexOfNextPipe(char *argument, int k);

