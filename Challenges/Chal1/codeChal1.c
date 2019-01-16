
#include <stdio.h>
#include <string.h>

void append(char* s, char c) {
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

int counter(char* string)
{
	int count = 0;
	int max = 0;
	char existing[26];
	for(int i = 0; i<26; i= i+1){
		for(int x =0; x<26; x = x+1){
			if (string[i]!=existing[x]){
				count=count+1;
				append (existing, string[i]);
			}else{
				if (count>max){
					max=count;
				}
				count=0;
			}
		}
	}
								

}


int main(void)
{
	char entry[26];
	int finalCount;

	printf("give me a string\n");
	scanf("%s" , entry);

	finalCount = counter(entry);

	printf("the substring is %1i characters ", finalCount);

}
