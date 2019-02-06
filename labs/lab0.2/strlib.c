
int strlen(char *str){
	int length=0;
	for (int i=0; str[i] != '\0'; i++)
		length++;
	return length;

}

char *stradd(char *origin, char *addition){
	int originLen = strlen(origin);
	int newLen;
	for (newLen = 0; addition[newLen] != '\0'; newLen++){
		origin[originLen+newLen]=addition[newLen];
	}
	origin[originLen+newLen]='\0';
	return origin;
		
}

int strfind(char *origin, char *substr){
	//int originLen, substrLen 
}
