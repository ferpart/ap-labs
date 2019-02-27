#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

#define nBytes 256
#define ERROR 1
#define SUCCESS 0

#define maxWordLen 30
#define maxColLen 1

void analizeWords(char *file);
int wordCounter(char *file);

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("please write a file to be sorted");
		return ERROR;
	}

	analizeWords(argv[1]);

	return 0;
}

void analizeWords(char *file)
{
	int fd,
	    fdS,
	    maxWords;

	char *buffer,
	     *bufferS;

	maxWords=wordCounter(file);
	printf("%d\n", maxWords);
	//char wordArray[maxWords][maxColLen][maxWordLen];


}

int wordCounter(char *file)
{
	int fd,
	    numOfWords,
	    i,
	    j,
	    nlFix,
	    jump;

	char *buffer,
	     *word;
	
	buffer=calloc(nBytes, sizeof(char));
	buffer[nBytes]='\0';
	
	word=calloc(nBytes, sizeof(char));
	word[0]='\0';
	word[nBytes]='\0';

	numOfWords=0;
	j=0;

	fd = open(file, O_RDONLY);

	if (fd == -1)
		exit(ERROR);

	while (read(fd, buffer, nBytes-1) > 0)
	{
		//printf("%c", buffer[0]);
		for (i=0; buffer[i]!='\n'; i++)
		{
			/*}else if (word[0]!='\0' && isspace(buffer[i])){
				//printf("%s\n", word);
				numOfWords++;
				//memset(word,'\0', maxWordLen+1);
				j=0;
			}*/
			word[i]=buffer[i];

		}
		
		if (buffer[i+1]=='\n')
		{
			//printf("%s\n", buffer);
			//printf("test\n");
			nlFix=3;
		}else
			nlFix=2;

		numOfWords++;
		jump=((i*sizeof(char)-strlen(buffer)*sizeof(char))+nlFix);

		lseek(fd, jump, SEEK_CUR);
		printf("%s\n", word);
		memset(buffer, '\0', nBytes);
		memset(word, '\0', nBytes); 
	}

	return numOfWords;
}



