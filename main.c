#include "headers.h"
#include "functions.h"

// CREATE THE MAKE FILE PLEASE! //

int main(void) {
	int address_mode = 1, command_number = 0, commands[10][BUFFERSIZE];
	char cwd[BUFFERSIZE] = "", home[BUFFERSIZE];
	getcwd(home, BUFFERSIZE);
	char user[BUFFERSIZE], host[BUFFERSIZE];
	getUser(user);
	gethostname(host, BUFFERSIZE);
	while(1) {
		printf("<%s@%s:", user, host);
		if(address_mode == 1) {
			printf("~");
		}
		printf("%s> ", cwd);
		char temp_command[BUFFERSIZE], command[BUFFERSIZE];
		scanf("%[^\n]%*c", temp_command);
		int i = 0;
		while(*(temp_command + i) != '\0') {
			i++;
		}
		*(temp_command + i) = ';';
		*(temp_command + i + 1) = '\0';
		i = 0;
		while(temp_command[i] == ' ') {
			i++;
		}
		int j = 0;
		while(temp_command[i] != '\0') {
			if(temp_command[i] == ';') {
				i++;
				if(command[j - 1] != ' ') {
					command[j] = ' ';
					j++;
				}
				command[j] = ';';
				j++;
				command[j] = ' ';
				j++;
				while(temp_command[i] == ' ') {
					i++;
				}
			}
			else if(temp_command[i] == '|') {
				i++;
				if(command[j - 1] != ' ') {
					command[j] = ' ';
					j++;
				}
				command[j] = '|';
				j++;
				command[j] = ' ';
				j++;
				while(temp_command[i] == ' ') {
					i++;
				}
			}
			else if(temp_command[i] == '<') {
				i++;
				if(command[j - 1] != ' ') {
					command[j] = ' ';
					j++;
				}
				command[j] = '<';
				j++;
				command[j] = ' ';
				j++;
				while(temp_command[i] == ' ') {
					i++;
				}
			}
			else if(temp_command[i] == '>') {
				i++;
				if(command[j - 1] != ' ') {
					command[j] = ' ';
					j++;
				}
				command[j] = '>';
				j++;
				if(temp_command[i] == '>') {
					i++;
					command[j] = '>';
					j++;
				}
				command[j] = ' ';
				j++;
				while(temp_command[i] == ' ') {
					i++;
				}
			}
			else {
				command[j] = temp_command[i];
				j++;
				i++;
			}
			if(temp_command[i] == ' ') {
				command[j] = ' ';
				j++;
			}
			while(temp_command[i] == ' ') {
				i++;
			}
		}
		command[j] = '\0';
		strcpy(&commands[command_number], command);
		int argument_count = getArgumentCount(command);
		char arguments[argument_count][BUFFERSIZE];
		for(int i = 0; i < argument_count; i++) {
			arguments[i][0] = '\0';
		}
		separateArguments(command, arguments, argument_count);
		for(int i = 0; i < argument_count; i++) {
			int term_count = getTermCount(arguments[i]);
			int pipe = checkPipe(arguments[i]), left_redirection = checkLeftRedirection(arguments[i], 0, BUFFERSIZE), right_redirection = checkRightRedirection(arguments[i]);
			int current_command[term_count];
			getTermIndices(arguments[i], current_command);
			if(pipe == 0 && (left_redirection != - 1 || right_redirection)) {
				int file_des[2];
				if(left_redirection != -1) {
					file_des[0] = open(&arguments[i][left_redirection + 1], O_RDONLY);
					dup2(file_des[0], 0);
					close(file_des[0]);
				}
				if(right_redirection) {
					int right_redirection_pointer = 0;
					while(arguments[i][right_redirection_pointer] != '>') {
						right_redirection_pointer++;
					}
					right_redirection_pointer += 2;
					if(right_redirection == 1) {
						file_des[1] = open(&arguments[i][right_redirection_pointer], O_WRONLY | O_CREAT | O_TRUNC);
					}
					if(right_redirection == 2) {
						file_des[1] = open(&arguments[i][right_redirection_pointer], O_WRONLY | O_CREAT | O_APPEND);
					}
					dup2(file_des[1], 1);
					close(file_des[1]);
				}
				char execution_statement[term_count + 1][BUFFERSIZE];
				execution_statement[0][0] = '\0';
				int j;
				for(j = 0; j < term_count; j++) {
					if(arguments[i][current_command[j]] != '<' && arguments[i][current_command[j]] != '>') {
						strcpy(&execution_statement[j], &arguments[i][current_command[j]]);
						strcat(&execution_statement[j], " ");
					}
					else {
						execution_statement[j][0] = '\0';
						break;
					}
				}
				execvp(&arguments[i], execution_statement);
			}
			else if(pipe || left_redirection != -1 || right_redirection) {
				int file_des[2][2], active = 0, k, l = -2, m;
				for(int j = 0; j < pipe; j++) {
					k = l + 2;
					l = findIndexOfNextPipe(arguments[i], k);
					m = checkLeftRedirection(arguments[i], k, l);
					if(m != -1) {
						file_des[active][0] = open(&arguments[i][m + 1], O_RDONLY);
						dup2(file_des[active][0], 0);
						close(file_des[active][0]);
						close(file_des[1 - active][1]);
					}
					else if(j != 0) {
						file_des[active][0] = open(file_des[1 - active][1], O_RDONLY); // ??
						dup2(file_des[active][0], 0);
						close(file_des[active][0]);
						close(file_des[1 - active][1]);
					}
					file_des[active][1] = open("temporary_shell_file.shl", O_CREAT | O_RDWR, 0777);
					printf("4\n");
					dup2(file_des[active][1], 1);
					close(file_des[active][1]);
					char execution_statement[BUFFERSIZE];
					execution_statement[0] = '\0';
					strcpy(execution_statement, &arguments[i][k]);
					strcat(execution_statement, " temporary_shell_file.shl");
					execvp(&arguments[i][k], execution_statement);
					//doPiping();
				}
				if(right_redirection != 0) {
					//findIndexOfRightRedirection();
					int output_fd; // BUT WE HAVE TO DO THIS BEFORE THE LAST PIPE OR LEFT REDIRECTION OR NONE!
					if(right_redirection == 1) {
						output_fd = open("", O_WRONLY | O_CREAT);
					}
					else {
						output_fd = open("", O_WRONLY | O_CREAT | O_APPEND);
					}
					//doRightRedirection();
				}
				//char deletion[2][BUFFERSIZE] = {"rm", "temporary_shell_file.shl"};
				//execvp("rm", deletion);
			}
			else if(strcmp(&arguments[i][current_command[0]], "pwd") == 0) {
				if(address_mode == 1) {
					printf("~");
				}
				printf("%s\n", cwd);
			}
			else if(strcmp(&arguments[i][current_command[0]], "cd") == 0) {
				if(term_count == 1) {
					chdir(home);
					cwd[0] = '\0';
				}
				else if(term_count == 2) {
					cdCommand(cwd, &arguments[i][current_command[1]], home, &address_mode);
				}
				else {
					printf("cd: too many arguments\n");
				}
			}
			else if(strcmp(&arguments[i][current_command[0]], "ls") == 0) {
				int a_flag = 0, l_flag = 0;
				if(term_count == 1) {
					lsCommand("./", a_flag, l_flag);
				}
				else if(arguments[i][current_command[1]] == '-') {
					if(strcmp(&arguments[i][current_command[1] + 1], "a") == 0) {
						a_flag = 1;
					}
					else if(strcmp(&arguments[i][current_command[1] + 1], "l") == 0) {
						l_flag = 1;
					}
					else if(strcmp(&arguments[i][current_command[1] + 1], "la") == 0 || strcmp(&arguments[i][current_command[1] + 1], "al") == 0) {
						a_flag = 1;
						l_flag = 1;
					}
					if(term_count == 2) {
						lsCommand("./", a_flag, l_flag);
					}
					else {
						for(int j = 2; j < term_count; j++) {
							if(term_count != 3) {
								printf("%s:\n", &arguments[i][current_command[j]]);
							}
							lsCommand(&arguments[i][current_command[j]], a_flag, l_flag);
							if(j != term_count - 1) {
								printf("\n");
							}
						}
					}
				}
				else if(arguments[i][current_command[1]] != '-' && term_count == 2){
					lsCommand(&arguments[i][current_command[1]], a_flag, l_flag);
				}
				else {
					for(int j = 1; j < term_count; j++) {
						if (term_count != 2) {
							printf("%s:\n", &arguments[i][current_command[j]]);
						}
						lsCommand(&arguments[i][current_command[j]], a_flag, l_flag);
						if(j != term_count - 1) {
							printf("\n");
						}
					}
				}
			}
			else if(strcmp(&arguments[i][current_command[0]], "echo") == 0) {
				if(term_count == 1) {
					printf("\n");
				}
				else {
					for(int j = 1; j < term_count; j++) {
						if(arguments[i][current_command[j]] == '"') {
							arguments[i][current_command[j + 1] - 2] = '\0';
							printf("%s\n", &arguments[i][current_command[j] + 1]);
							arguments[i][current_command[j + 1] - 2] = '"';
						}
						else {
							printf("%s\n", &arguments[i][current_command[j]]);
						}
					}
				}
			}
			else if(strcmp(&arguments[i][current_command[0]], "pinfo") == 0) {
				if(term_count == 1) {
					pid_t pid = getpid();
					pinfoCommand(pid);
				}
				else if(term_count == 2) {
					pid_t pid = 0;
					for(int j = 0; arguments[i][current_command[1] + j] != '\0'; j++) {
						pid *= 10;
						pid += arguments[i][current_command[1] + j] - '0';
					}
					pinfoCommand(pid);
				}
				else {
					printf("pinfo: too many arguments\n");
				}
			}
			else if(strcmp(&arguments[i][current_command[0]], "setenv") == 0) {
				if(term_count == 1) {
					printf("Bahutaye zyaada information de di bhaaisahab\n");
				}
				if(term_count == 2) {
					setenv(&arguments[i][current_command[1]], "", 1);
				}
				else if(term_count == 3) {
					setenv(&arguments[i][current_command[1]], &arguments[i][current_command[2]], 1);
				}
				else {
					printf("setenv: too many arguments\n");
				}
			}
			else if(strcmp(&arguments[i][current_command[0]], "unsetenv") == 0) {
				if(term_count == 1) {
					printf("Sorry deedi\n");
				}
				else if(term_count == 2) {
					unsetenv(&arguments[i][current_command[1]]);
				}
				else {
					printf("unsetenv: too many arguments\n");
				}
			}
			else if(strcmp(&arguments[i][current_command[0]], "quit") == 0) {
				return 0;
			}
			else {
				int background_process = 0;
				if(term_count > 1 && strcmp(&arguments[i][current_command[1]], "&") == 0) {
					background_process = 1;
				}
				pid_t pid;
				pid = fork();
				if(pid == 0) {
					int *temp_string[term_count + 1];
					for(int j = 0; j < term_count; j++) {
						temp_string[j] = &arguments[i][current_command[j]];
					}
					if(background_process == 0) {
						temp_string[term_count] = '\0';
					}
					else {
						temp_string[term_count - 1] = '\0';
					}
					int x = execvp(temp_string[0], temp_string); // ABSOLUTE ADDRESSES KA KYA??
					if(x < 0) {
						//perror( "Error");
						printf("%s: command not found\n", temp_string[0]);
					}
					else if(background_process == 1) {
						printf("Starting %s in background\n", &arguments[i][current_command[0]]); // ?!
					}
				}
				else if(pid > 0) {
					if(background_process == 0) {
						wait(NULL);
					}
				}
			}
		}
		if(command_number != 9) {
			command_number++;
		}
		else {
			command_number = 0;
		}
	}
	return 0;
}
