#include <stdio.h>

int strlen(char *str);
char *stradd(char *origin, char *addition);
int strfind(char *origin, char *substr);

int main(int argc, char **argv)
{
	int length = strlen(argv[1]);
	printf("Initial Length		: %d\n", length);

	stradd(argv[1], argv[2]);
	printf("New String		: %s\n", argv[1]);

	printf("SubString was found	: ");
	if (strfind(argv[1], argv[3]))
		printf("yes\n");
	else
		printf("no\n");
	
}
