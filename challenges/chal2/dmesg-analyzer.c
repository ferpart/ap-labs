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

#define row 200
#define col 100

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
    
	
	int fd,
	    fdN,
	    j=0,
	    flag=0,
	    jump=0,
	    login=0,
	    arrayin=1,
	    arrflag=0;

	char *buffer, 
	     *temp,
	     *temptime,
	     *tempdesc;
	     
	char catarray[row][col][nBytes];

	buffer=calloc(nBytes, sizeof(char));
	buffer[nBytes]='\0';

	temp=calloc(maxlogLen, sizeof(char));
	temp[maxlogLen]='\0';

	tempdesc=calloc(nBytes, sizeof(char));
	tempdesc[nBytes]='\0';

	temptime=calloc(logStart, sizeof(char));
	temptime[logStart]='\0';

	memset(catarray, '\0', sizeof catarray);
	
	strcpy(catarray[0][0], "General:");

	fd = open(logFile, O_RDONLY);
	fdN= open("report.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);

	if (fd == -1)
       		exit(ERROR);
	
	while (read(fd, buffer, nBytes-1) > 0)
	{
    		for (int i=0; buffer[i]!='\0'; i++)
		{
			if (buffer[i]!='\n')
			{
				if (i <logStart-1)
				{
					temptime[login]=buffer[i];
					login++;
				}

				if (i>=logStart)
				{	
					if (flag !=1 && i<=maxlogLen-1)
						temp[j]=buffer[i];

					tempdesc[j]=buffer[i];

					if (((buffer[i]==':' && (buffer[i+1]==' ' 
							|| buffer[i+1]=='\n'))
							&& i<=maxlogLen+logStart)
					   		&& flag!=1)		
					{
							
						flag=1;
						for (int l=0; l<=row; l++)
						{
							if(strcmp(temp, 
								  catarray[l][0] 
								  )!= 0)
							{
								arrflag=1;
							}else
							{
								arrflag=0;
								memset(tempdesc, '\0', nBytes);
								j=0;
								j--;
								break;
							}

						}
						if (arrflag)
						{
							//printf("%s\n", temp);
							strcpy(catarray[arrayin]
							       [0], temp);
							memset(catarray[arrayin
								+1][0], '\0',
								nBytes);	

							arrflag=0;
							arrayin++;
							memset(tempdesc, '\0', nBytes);
							j=0;
							j--;
						}

					}
					j++;

				}
			}
			else
			{
				
				for (int l=1; l<=row-1; l++){
					if (strcmp(temp, catarray[l][0])==0)
					{
						for (int m=1; m <= col-1; m++)
						{
							//printf("%d\n", m);
							if (*catarray[l][m]=='\0')
							{
								memset(catarray[l][m], '\0', nBytes);
								strcpy(catarray[l][m], temptime);
								strcat(catarray[l][m], " ");
								strcat(catarray[l][m], tempdesc);
								break;
							}
						}
						break;
					}
					else if (l==row-1)
					{
						for (int m=1; m <= col-1; m++)
						{
							if (*catarray[0][m]=='\0'
							   )
							{
								memset(catarray[0][m], '\0', nBytes);
								strcpy(catarray[0][m], temptime);
								strcat(catarray[0][m], " ");
								strcat(catarray[0][m], tempdesc);
								break;
							}
						}
					}				
				}	


				flag=0,
				j=0,
				login=0;

				jump = (i*sizeof(char)-strlen(buffer)*
						sizeof(char))+1;
				
				lseek(fd, jump , SEEK_CUR);

				memset(temp, '\0' ,maxlogLen);
				memset(tempdesc, '\0', nBytes);
				memset(temptime, '\0', logStart);
				
				break;
			}
		}
		
		memset(buffer, '\0', nBytes);	
    	}
	for (int r=0; r<=row-1; r++)
	{
		if (*catarray[r][0]!='\0'){
			write(fdN, catarray[r][0], strlen(catarray[r][0]));
			write(fdN, "\n", 1);
		}
		for (int c=1; c<=col-1; c++)
		{
			if (*catarray[r][c]!='\0')
			{
		        	write(fdN, catarray[r][c], strlen(catarray[r][c]));
				write(fdN, "\n", 1);
			}
		}
	}
	close(fd);
	close(fdN);
    printf("Report is generated at: [%s]\n", report);
}


