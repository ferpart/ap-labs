#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define REPORT_FILE "report.txt"
#define nBytes 256
#define ERROR 1
#define SUCCESS 0

#define maxlogLen 50
#define logStart 15

void analizeLog(char *logFile, char *report);

int main(int argc, char **argv)
{

    if (argc < 2)
    {
	printf("Usage:./dmesg-analizer.o logfile.txt\n");
	return 1;
    }

    analizeLog(argv[1], REPORT_FILE);

    return 0;
}

void analizeLog(char *logFile, char *report)
{
	printf("Generating Report from: [%s] log file\n", logFile);

    	// Implement your solution here.
    
    	int fd;
	//char * line = NULL;
	//size_t len = 0;
	
	fd = open(logFile, O_RDONLY);
	if (fd == -1)
       		exit(ERROR);

	char *buffer, *temp;
	buffer=calloc(nBytes, sizeof(char));
	temp=calloc(maxlogLen, sizeof(char));
	temp[nBytes]='\0';
	buffer[maxlogLen]='\0';
	//int i=0, 
	int j=0,
	    k=0, 
	    flag=0,
	    jump=0;
    	
	while (read(fd, buffer, nBytes-1) > 0)
	{
    		for (int i=0; buffer[i]!='\0'; i++)
		{
			//printf("%d num test\n", i );
			//printf("%c\n", buffer[i+1]);
			if (buffer[i]!='\n')
			{
				//printf("%c", buffer[i]);
				if (i <=maxlogLen+logStart && i>=logStart && 
						flag!=1)
				{
					//printf("test\n");
					temp[j]=buffer[i];
					//printf("%c\n", temp[j]);
					if (buffer[i]==':' && (buffer[i+1]==' ' 
							|| buffer[i+1]=='\n'))		
					{
							
						flag=1;
						printf("%s\n", temp);
					}
					j++;

				}

				/*if (flag)
				{	
					//printf("test");
					printf("%s\n", temp);
				}*/


			}else
			{
				flag=0,
				j=0;
				
				jump = (i*sizeof(char)-strlen(buffer)*sizeof(char))+1;
				
				lseek(fd, jump , SEEK_CUR);

				memset(temp, '\0' ,maxlogLen);
				
				break;
			}
		}
		
		memset(buffer, '\0', nBytes);	
    	}	
	
	close(fd);
    printf("Report is generated at: [%s]\n", report);
}


