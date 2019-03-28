#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>

#define DIRSIZE 512
#define nBytes 512

void clear(),
topWriter(char *tempFile),
filePrinter(int fd),
interruptionWriter(int signal), forceExit(int signal), cleanup(void);

char *statusExplorer(char *path, int openFiles);

int openFileExplorer(char *path);

int main()
{
	// Place your magic here

	if (signal(SIGINT, interruptionWriter) == SIG_ERR)
		printf("Signal map wasn't successful");

	if (signal(SIGQUIT, forceExit) == SIG_ERR)
		printf("Signal map wasn't successful");

	clear();
	while (1) {
		clear();
		topWriter(".temp");
	}

	atexit(cleanup);

	return 0;
}

void clear()
{
	printf("\e[1;1H\e[2J");
}

void topWriter(char *tempFile)
{

	DIR *dir;

	struct dirent *ent;

	char *procDir, *result;

	int fd;

	procDir = calloc(DIRSIZE, sizeof(char));
	result = calloc(nBytes, sizeof(char));

	fd = open(tempFile, O_RDWR | O_CREAT, S_IRWXO);

	if (fd == -1) {
		close(fd);
		printf("Couldn't create file");
		exit(EXIT_FAILURE);
	}
	sprintf(result,
		"____________________________________________________________________________________________________________________________________\n");
	write(fd, result, strlen(result));
	//result[0]='\0';
	sprintf(result,
		"|  %-9s|  %-9s|  %-41s|  %-15s|  %-15s|  %-9s|  %-12s|\n",
		"PID", "Parent", "Name", "State", "Memory", "#Threads",
		"Open Files");
	write(fd, result, strlen(result));

	sprintf(result,
		"|-----------|-----------|-------------------------------------------|-----------------|-----------------|-----------|--------------|\n");
	write(fd, result, strlen(result));

	strcpy(procDir, "/proc");

	dir = opendir(procDir);

	if (dir != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (isdigit(ent->d_name[0])) {
				strcpy(procDir, "/proc/");
				strcat(procDir, ent->d_name);

				sprintf(result, "%s", statusExplorer(procDir,
								     openFileExplorer
								     (procDir)));
				if (strlen(result) > 100)
					write(fd, result, strlen(result));

				memset(procDir, '\0', DIRSIZE);
				memset(result, '\0', nBytes);
			}

		}

	}
	closedir(dir);

	sprintf(result,
		"‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
	write(fd, result, strlen(result));

	filePrinter(fd);

	close(fd);

}

char *statusExplorer(char *path, int openFiles)
{

	char *finalFile, *buffer, *child, *status, *returnValue;

	char *pid, *ppid, *name, *state, *memory, *threads;

	int fd, flag, jump, j = 0;

	double mbs = 0;

	finalFile = calloc(DIRSIZE + 7, sizeof(char));
	buffer = calloc(nBytes, sizeof(char));
	child = calloc(8, sizeof(char));
	status = calloc(13, sizeof(char));

	pid = calloc(6, sizeof(char));
	ppid = calloc(6, sizeof(char));
	name = calloc(256, sizeof(char));
	state = calloc(13, sizeof(char));
	memory = calloc(20, sizeof(char));
	threads = calloc(2, sizeof(char));

	returnValue = calloc(256, sizeof(char));

	strcpy(finalFile, path);
	strcat(finalFile, "/status");

	fd = open(finalFile, O_RDONLY);

	if (fd == -1) {
		close(fd);
		return "";
	}

	while (read(fd, buffer, nBytes - 1) > 0) {
		flag = 0;
		for (int i = 0; buffer[i] != '\0'; i++) {
			if (buffer[i] != '\n') {
				if (buffer[i] != ':' && flag == 0) {
					child[i] = buffer[i];
				} else if (buffer[i] == ':') {
					flag = 1;
				}

				if (flag) {
					if (buffer[i] != ':'
					    && buffer[i] != '\t') {
						if (strcmp(child, "Pid") == 0
						    || strcmp(child,
							      "PPid") == 0
						    || strcmp(child,
							      "Name") == 0
						    || strcmp(child,
							      "State") == 0
						    || strcmp(child,
							      "Threads") == 0
						    || strcmp(child,
							      "VmSize") == 0) {
							status[j] = buffer[i];
							j++;
						}

					}
					if (buffer[i + 1] == '\n') {
						if (strcmp(child, "Pid") == 0) {
							strcpy(pid, status);
							//printf("%-10s", pid); 
						} else if (strcmp(child, "PPid")
							   == 0) {
							strcpy(ppid, status);
							//printf("%s\n", ppid);
						} else if (strcmp(child, "Name")
							   == 0) {
							strcpy(name, status);
						} else
						    if (strcmp(child, "State")
							== 0) {
							strcpy(state, status);
						} else
						    if (strcmp(child, "VmSize")
							== 0) {
							mbs =
							    (atoi(status) +
							     .0) / 1000;
							sprintf(memory, "%.4fM",
								mbs);
						} else
						    if (strcmp(child, "Threads")
							== 0) {
							strcpy(threads, status);
						}
						flag = 0;
						memset(status, '\0', 13);
					}
				}
			} else {
				jump = (i * sizeof(char) - strlen(buffer) *
					sizeof(char)) + 1;

				j = 0;

				lseek(fd, jump, SEEK_CUR);

				memset(child, '\0', 8);
				memset(buffer, '\0', nBytes);
			}
		}
	}

	close(fd);
	if (memory[0] == '\0')
		strcpy(memory, "0.000M");

	sprintf(returnValue,
		"|  %-9s|  %-9s|  %-41s|  %-15s|  %-15s|  %-9s|  %-12d|\n", pid,
		ppid, name, state, memory, threads, openFiles);

	return returnValue;
}

int openFileExplorer(char *path)
{
	DIR *dirE;

	struct dirent *ent;

	char *procDir;

	int dirs = 0;

	procDir = calloc(DIRSIZE, sizeof(char));

	strcpy(procDir, path);
	strcat(procDir, "/fd");

	dirE = opendir(procDir);

	if (dirE != NULL) {
		while ((ent = readdir(dirE)) != NULL) {
			if (isdigit(ent->d_name[0])) {
				dirs++;
			}

		}

	}
	closedir(dirE);

	return dirs;
}

void filePrinter(int fd)
{
	char *buffer;

	buffer = calloc(nBytes, sizeof(char));

	lseek(fd, 0, SEEK_SET);

	while (read(fd, buffer, nBytes - 1) > 0) {
		printf("%.*s", (int)strlen(buffer), buffer);
		memset(buffer, '\0', nBytes);
	}

}

void interruptionWriter(int signal)
{
	char date[11], fileTitle[25];

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	sprintf(date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

	strcpy(fileTitle, "mytop-status-");
	strcat(fileTitle, date);

	topWriter(fileTitle);

}

void forceExit(int signal)
{
	cleanup();
	exit(EXIT_SUCCESS);
}

void cleanup(void)
{
	remove(".temp");
}
