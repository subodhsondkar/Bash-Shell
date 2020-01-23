#include "./headers.h"

void pinfoCommand(pid_t pid) {
	printf("pid\t\t%d\n", pid);
	char path[BUFFERSIZE] = "/proc/", temp_path[2];
	int i = 0, temp_pid = pid;
	char temp0[BUFFERSIZE], temp1[BUFFERSIZE];
	for(; temp_pid; i++) {
		temp0[i] = '0' + temp_pid % 10;
		temp_pid/= 10;
	}
	temp0[i] = '\0';
	int path_length = i + 6;
	i--;
	for(; i >= 0; i--) {
		temp1[0] = temp0[i];
		temp1[1] = '\0';
		strcat(path, temp1);
	}
	strcpy(temp_path, path);
	strcat(temp_path, "/stat");
	printf("%s\n", temp_path);
	int fd_stat = open(temp_path, O_RDONLY);
	char temp_stat[BUFFERSIZE], *token;
	read(fd_stat, temp_stat, BUFFERSIZE);
	token = strtok(temp_stat, " ");
	token = strtok(NULL, " ");
	token = strtok(NULL, " ");
	printf("Process Status\t{%s}\n", token);
	close(fd_stat);
	temp_path[path_length] = '\0';
	strcat(temp_path, "/statm");
	printf("%s\n", temp_path);
	int fd_mem = open(temp_path, O_RDONLY);
	char temp_mem[BUFFERSIZE];
	read(fd_mem, temp_mem, BUFFERSIZE);
	token = strtok(temp_mem, " ");
	printf("Memory\t\t%s\n", token);
	close(fd_mem);
	temp_path[path_length] = '\0';
	strcat(path, "/exe");
	printf("%s\n", temp_path);
	char temp_exe[BUFFERSIZE];
	readlink(temp_path, temp_exe, BUFFERSIZE);
	printf("Executable path\t%s\n", temp_exe);
}

