
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
	int  x, y;

	x = strlen(origin);
	y = strlen(substr);

	if (y==0)
		return 1;
	if (x<y)
		return 0;
		
	for (int i=0; origin[i] != '\0'; i++){
		if (origin[i]==substr[0]){
			for (int j=0; substr[j] != '\0'; j++){
				if (origin[i+j] == substr[j]){
					if(j == y-1){
						return 1;
					}
				}
				else{
					break;
				}

			}
		}
	}
	return 0; 
}


