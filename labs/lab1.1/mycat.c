#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define nbytes 128
#define ERROR 1
#define SUCCESS 0 

void main (int argc, char **argv)
{
	int fd, fdC;

	if (argc == 2){
		fd = open(argv[1], O_RDONLY);

		if (fd == -1){

			/*The lines 25-29 could be substituted using the 
			 * perror() function, but weren't used because the 
			 * write() system call was specificied.
			 */

			
			char *message= ": No such file or directory\n"; 

			char *errPrint;
			errPrint=calloc(strlen(argv[1])+strlen(message)+1, 
					sizeof(char));
			strcpy(errPrint, argv[1]);
			strcat(errPrint, message);
			int length= strlen(errPrint);
			write(1, errPrint , length);
			
			exit(ERROR);
		}

		char *buffer;
		buffer=calloc(nbytes, sizeof(char));
		while (read(fd, buffer, nbytes-1) > 0){
			printf("%s", buffer);
			memset(buffer, '\0', nbytes);
		}
		close(fd);

	}else
		exit(ERROR);


	exit(SUCCESS);

}		
