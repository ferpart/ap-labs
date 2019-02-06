#include <stdio.h>




int rerun (char *a){
	printf("%s\n", a);
	if (a[0] != '\0')
		rerun(&a[1]);
}

void main(){
	rerun("test");
}
