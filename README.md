# Bash-Shell

## Aim
- To implement a shell in C.
- Built-in commands such as cd, pwd, echo are to be coded along with ls (including flags).
- System commands such as vim, evince can be executed in foreground as well as in background.
- A command called "pinfo" must be coded which gives information about the required process.

## Commands:
- Command | Property
- pwd; | prints the name of current directory.
- cd [dir] | if dir is specified, changes directory to dir, otherwise, changes directory to shell home.
- echo string | prints the string in the next line.
- ls -[al] [dir] | prints the contents of dir, with the option of long form output, or of all files.
- sys-com args | implements sys-com with args as arguments.
- pinfo [pid] | if pid is mentioned, gives information of shell, otherwise, gives information of pid.
- exit | quits the shell.

## Functions:
- Function | Property
- void getUser(char *user); | copies the username to the input string.
- int getArgumentCount(char *command); | returns the number of subcommands in the given command (separated by semicolons).
- void separateArguments(char *command, char arguments[][BUFFERSIZE], int argument_count); | all the subcommands are stored in different subarrays of the array arguments.
- int getTermCount(char *argument); | returns the number of terms in a subcommand.
- void getTermIndices(char argument[BUFFERSIZE], int *current_command); | stores the indices of the terms in a subcommand in an array.
- void cdCommand(char* cwd, char *path, int home_length); | implements cd.
- int lsCommand(char *path, int a_flag, int l_flag); | implements ls.
- void pinfoCommand(pid_t pid); | implements pinfo.

