/*
 * Code not currently working, as an unexpected error is ocurring
 */


#include <stdio.h>
//#include <string.h>

/*int strlen(char *str){
        int length=0;
        for (int i=0; str[i] != '\0'; i++)
		length++;
        return length;

}*/


int maxSubsting(char *string){
	
	char temp[10];
	int flag=0;
	int tempint=0;
	int k =0;
	temp[0]=" ";

	for (int i =0; string[i]!= '\0'; i++){
		for (int j = 0; temp[j] !='\0'; j++){
			if (temp[j]!=string[i])
				flag=1;
			else{
				flag=0;
				break;
			}
		}
		if (flag){
			temp[k]=string[i];
			temp[k+1]=" ";
			k++;
			if (k>tempint)
				tempint=k;
		}else{

			temp[0]=string[i];
			temp[1]=" ";		
			k=0;
			
		
		}
		/*if (k>tempint){
			tempint = k;
			k=0;
		}*/
	}
	/*if (k>tempint){
		tempint = k;	
	}*/

	printf("%d\n", tempint);
	return tempint;
}


/*int main(int argc, char *argv[]){
	maxSubsting(argv[1]);
	return 0;
}*/


int main(){
	maxSubsting("testtesta");
	return 0;
}
