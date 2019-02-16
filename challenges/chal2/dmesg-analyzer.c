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

#define row 481
#define col 20

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
	    k=0,
	    p=0,
	    flag=0,
	    jump=0,
	    arrayin=1,
	    arrflag=0;

	char *buffer, 
	     *temp,
	     *tempdesc,
	     *tempfail,
	     catarray[row][col][maxlogLen];

	buffer=calloc(nBytes, sizeof(char));
	buffer[nBytes]='\0';

	temp=calloc(maxlogLen, sizeof(char));
	temp[maxlogLen]='\0';

	tempdesc=calloc(nBytes, sizeof(char));
	tempdesc[nBytes]='\0';

	tempfail=tempdesc;
	
	memset(catarray, '\0', sizeof catarray);
	
	strcpy(catarray[0][0], "General:");

	fd = open(logFile, O_RDONLY);
	fdN= open("report.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);

	if (fd == -1)
       		exit(ERROR);
	
	while (read(fd, buffer, nBytes-1) > 0)
	{
    		for (int i=0; buffer[i]!='\0'; i++)
		{
			if (buffer[i]!='\n')
			{
				if (i <=maxlogLen+logStart && i>=logStart && 
						flag!=1)
				{
					temp[j]=buffer[i];

					if (buffer[i]==':' && (buffer[i+1]==' ' 
							|| buffer[i+1]=='\n'))		
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
								break;
							}

						}
						if (arrflag)
						{
							strcpy(catarray[arrayin]
							       [0], temp);
							memset(catarray[arrayin
								+1][0], '\0',
								maxlogLen);	

							arrflag=0;
							arrayin++;
						}
					}
					j++;

				}else if (flag)
				{
					
					tempdesc[k]=buffer[i+1];
					k++;		
				}
				if (i>=logStart ){
						
					tempfail[p]=buffer[i];
					p++;
				}
				


			}
			else
			{
				if (flag == 0)
				{
					tempfail[p+1]='\n';
					tempdesc=tempfail;
				}
				for (int l=0; l<=row; l++){
					//printf("%s\n" , tempdesc);
					if (strcmp(temp, catarray[l][0])==0)
					{
						for (int m=1; m <= col; m++)
						{
							//printf("%d\n", m);
							if (*catarray[l][m]=='\0'
							   )
							{ 
								strcpy(catarray[
									l][m], 
									tempdesc
								      );
								
								break;
							}
						}
					}else
					{
						for (int m=1; m <= col; m++)
						{
							if (*catarray[0][m]=='\0'
							   )
							{
								strcpy(catarray
								       [0][m],
								       tempdesc
								       );
								break;
							}
						}
					}				
				}	


				flag=0,
				j=0,
				k=0;
				//printf("%s", tempfail);
				jump = (i*sizeof(char)-strlen(buffer)*
						sizeof(char))+1;
				
				lseek(fd, jump , SEEK_CUR);

				memset(temp, '\0' ,maxlogLen);
				memset(tempdesc, '\0', nBytes);
				
				tempfail=tempdesc;

				break;
			}
		}
		
		memset(buffer, '\0', nBytes);	
    	}
	
	for (int r=0; r<=row; r++)
	{
		write(fdN, catarray[r][0], strlen(catarray[r][0]));
		write(fdN, "\n", 1);
		//printf("%s\n", catarray[r][0]);
		/*for (int c=1; c<=col; c++)
		{
			write(fdN, "	", 1);
		        write(fdN, catarray[r][c], strlen(catarray[r][c]));
			//write(fdN, "\n", 1);
			//printf("	%s\n", catarray[r][c]);	
		}*/
	}
	close(fd);
	close(fdN);
    printf("Report is generated at: [%s]\n", report);
}


