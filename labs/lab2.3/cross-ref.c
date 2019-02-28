#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

#define nBytes 256
#define ERROR 1
#define SUCCESS 0

#define maxWordLen 31
#define maxColLen 1

#define WORDSSTORED 4000

#define STOPWORDS 154

void wordCounter(char *file);
void listPrinter(char *list[WORDSSTORED][2]);
int stopWordCheck(char *word);
char *strlowr(char *str);

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("please write a file to be sorted");
		return ERROR;
	}

	wordCounter(argv[1]);

	return 0;
}

void wordCounter(char *file)
{
	int fd,
	    lineNumber,
	    i,
	    j,
	    nlFix,
	    jump;

	char *buffer,
	     *word,
	     *lineNumberStr,
	     *wordLower;

	char *wordDictionary[WORDSSTORED][2];
	
	for (int k=0; k<WORDSSTORED-1; k++)
		wordDictionary[k][0]=calloc(1, sizeof(char));

	buffer=calloc(nBytes, sizeof(char));
	buffer[nBytes]='\0';
	
	word=calloc(maxWordLen, sizeof(char));
	word[maxWordLen]='\0';
	
	lineNumberStr=calloc(4, sizeof(char));
	lineNumberStr[4]='\0';

	wordLower=calloc(maxWordLen, sizeof(char));
	wordLower[maxWordLen]='\0';

	lineNumber=1;
	j=0;

	fd = open(file, O_RDONLY);

	if (fd == -1)
		exit(ERROR);

	while (read(fd, buffer, nBytes-1) > 0)
	{
		for (i=0; buffer[i]!='\n'; i++)
		{
			if (isalpha(buffer[i]) && buffer[i+1]!='\'' &&
						  (isspace(buffer[i+1]) ||
						   ispunct(buffer[i+1]))){
				word[j] = buffer[i];

				wordLower=strlowr(word);

				if (stopWordCheck(wordLower)!=0){

					sprintf(lineNumberStr, "%d", lineNumber);
					for (int k=0; k<WORDSSTORED-1; k++){
						if (strcmp(wordDictionary[k][0], wordLower)){
							if (wordDictionary[k][0][0]=='\0'){
								wordDictionary[k][0]=calloc(strlen(wordLower), sizeof(char));
								wordDictionary[k][1]=calloc(nBytes , sizeof(char));
								strcpy(wordDictionary[k][0], wordLower);
								strcpy(wordDictionary[k][1], lineNumberStr);
								break;
							}
						}else{
							strcat(wordDictionary[k][1], ", "); 
							strcat(wordDictionary[k][1], lineNumberStr);
							break;
						}
					}
					memset(lineNumberStr, '\0', 4);
				}
				j=0;
				memset(word, '\0', maxWordLen);
				memset(wordLower, '\0', maxWordLen);

			}else if (isalpha(buffer[i]) || (isalpha(buffer[i-1]) &&
							buffer[i]=='\'')){
				word[j] = buffer[i];
				j++;
			}	

		}
		
		if (buffer[i+1]=='\n')
		{
			//printf("%s\n", buffer);
			//printf("test\n");
			nlFix=3;
			lineNumber++;
		}else
			nlFix=1;
		
		lineNumber++;

		jump=((i*sizeof(char)-strlen(buffer)*sizeof(char))+nlFix);

		lseek(fd, jump, SEEK_CUR);
		memset(buffer, '\0', nBytes);
		memset(word, '\0', maxWordLen); 
	}
	listPrinter(wordDictionary);
}

int stopWordCheck(char *word){

	int flag = 1;
	char *stopWordList[STOPWORDS] = {"a", "about", "above", "after", 
		"again", "against", "all", "am", "an", "and", "any", "are", 
		"as", "at", "be", "because", "been", "before", "being", "below",
	       	"between", "both", "but", "by", "could", "did", "do", "does", 
		"doing", "down", "during", "each", "few", "for", "from", 
		"further", "had", "has", "have", "having", "he", "he'd", 
		"he'll", "he's", "her", "here", "here's", "hers", "herself", 
		"him", "himself", "his", "how", "how's", "i", "i'd", "i'll", 
		"i'm", "i've", "if", "in", "into", "is", "it", "it's", "its", 
		"itself", "let's", "me", "more", "most", "my", "myself", "nor",
	       	"of", "on", "once", "only", "or", "other", "ought", "our", 
		"ours", "ourselves", "out", "over", "own", "same", "she", 
		"she'd", "she'll", "she's", "should","so", "some", "such", 
		"than", "that", "that's", "the", "their", "theirs", "them", 
		"themselves", "then", "there", "there's", "these", "they", 
		"they'd", "they'll", "they're", "they've","this", "those", 
		"through", "to", "too", "under", "until", "up", "very", "was", 
		"we", "we'd", "we'll", "we're", "we've", "were", "what", 
		"what's", "when", "when's", "where", "where's","which", "while", 
		"who", "who's", "whom", "why", "why's", "with", "would", "you", 
		"you'd", "you'll", "you're", "you've", "your", "yours", 
		"yourself", "yourselves"};	
	
	for (int i=0; i<STOPWORDS-1; i++){
		if (strcmp(word, stopWordList[i])==0){
			//printf("test\n");
			flag=0;
			break;		
		}
	}	
	if (flag==0)
		return 0;
	return 1;

}

char *strlowr(char *str)
{
  unsigned char *p = (unsigned char *)str;

  while (*p) {
     *p = tolower((unsigned char)*p);
      p++;
  }

  return str;
}

void listPrinter(char *list[WORDSSTORED][2]){

	for (int i=0; i<WORDSSTORED-1; i++){
		if (list[i][0][0]!='\0'){
		printf("%-20s:", list[i][0]);
		printf("%s\n", list[i][1]);
		}else{
			break;
		}
	}
}
