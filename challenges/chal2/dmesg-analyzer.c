#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define REPORT_FILE "report.txt"
#define nBytes 256
#define ERROR 1
#define SUCCESS 0

void analizeLog(char *logFile, char *report);

int main(int argc, char **argv) {

    if (argc < 2) {
	printf("Usage:./dmesg-analizer.o logfile.txt\n");
	return 1;
    }

    analizeLog(argv[1], REPORT_FILE);

    return 0;
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

    // Implement your solution here.
    
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(logFile, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
    	//printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
	for (int i = 15; line[i-1]==':' && i!=45; i++){
		printf("%s", line[i]);
	}
    }		
	

    printf("Report is generated at: [%s]\n", report);
}
