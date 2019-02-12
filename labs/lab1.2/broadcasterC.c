#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

#define ERROR 1
#define SUCCESS 0 

int main (int argc, char **argv)
{

	char *finalString;
	int fd;

	int stringLen=0;
	
	if (argc>1){	

		for (int i=1; i!=argc; i++)
			stringLen+=strlen(argv[i])+2;
	
		finalString=calloc(stringLen, sizeof(char));
	
		for (int i=1; i!=argc; i++){
			strcat(finalString, argv[i]);
			strcat(finalString, " ");
		}
		
		finalString[stringLen-1]='\n';
		finalString[stringLen]='\0';
		
		DIR *dir;
		struct dirent *ent;
		char *finalFile;
		char dirName[256];

		finalFile=calloc(strlen(dirName)+9, sizeof(char));
		strcpy(finalFile, "/dev/pts/");

		if ((dir = opendir(finalFile)) != NULL){
			while ((ent = readdir (dir)) != NULL) {
				strcpy(dirName, ent->d_name);
				if (isdigit(dirName[0])){	
					
					strcpy(finalFile, "/dev/pts/");
					strcat(finalFile, dirName);
					
					fd = open(finalFile, O_WRONLY);
					
					if (fd == -1)
						return ERROR;
					
					write(fd, "\n", 2);
					write(fd, finalString, stringLen);
					close(fd);
				}
				memset(dirName, '\0', 256);
				memset(finalFile, '\0', strlen(dirName)+9);
  			}
  		closedir (dir);
		
		}
		
		return SUCCESS;
	}else
		return ERROR;
}

