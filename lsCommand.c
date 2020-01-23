#include "./headers.h"

int lsCommand(char *path, int a_flag, int l_flag) {
	char dirname[BUFFERSIZE];
	DIR *dirp = opendir(path);
	struct dirent *d;
	int i = 0;
	while(path[i] != '\0') {
		i++;
	}
	if(path[i - 1] != '/') {
		path[i] = '/';
		path[i + 1] = '\0';
	}
	if(dirp == NULL) {
		perror("ls");
		return -1;
	}
	while(d = readdir(dirp)) {
		if(d->d_name[0] != '.' || a_flag == 1) {
			if(l_flag == 1) {
				struct stat file_stat;
				char temp_path[BUFFERSIZE];
				strcpy(temp_path, path);
				strcat(temp_path, d->d_name);
				stat(temp_path, &file_stat);
				printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
				printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
				printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
				printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
				printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
				printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
				printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
				printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
				printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
				printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
				printf("\t%ld\t", file_stat.st_nlink);
				printf("%s\t", getpwuid(geteuid())->pw_name);
				printf("%s\t", getgrgid(getegid())->gr_name);
				printf("%ld\t", file_stat.st_size);
				char mtime[20];
				strftime(mtime, 20, "%Y-%m-%d %H:%M:%S", localtime(&file_stat.st_mtime));
				printf("%s\t", mtime);
			}
			printf("%s\n", d->d_name);
		}
	}
	return 0;
}

