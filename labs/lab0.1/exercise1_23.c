#include<stdio.h>
#include<stdlib.h>

void rcomment(int c, FILE *doc, FILE *fDoc);
void incomment(FILE *doc);
void echo_quote(int c, FILE *doc, FILE *fDoc);

int main(void)
{
	FILE *document;
	FILE *finalDoc;	
        char filename[100]="";

        printf("Give me the file you want comments removed from:\n");
        scanf("%s", filename);

        document=fopen(filename, "r");
                if (document==NULL)
                {
                        printf("\n%s\" File not found", filename);
                        exit(1);
                }
	finalDoc=fopen("noComments.c", "w");
		if (finalDoc == NULL){
			printf("\nFile could not be created");
			exit(1);
		}	


	int c;

    	while((c= getc(document)) !=EOF){
		rcomment(c, document, finalDoc);
	}

    	return 0;
}

void rcomment(int c, FILE *doc, FILE *fDoc)
{
    int d;
    if( c == '/')
 {
        if((d=getc(doc))=='*')
         incomment(doc);
        else if( d == '/')
        {
            putc(c, fDoc);
            rcomment(d, doc, fDoc);
        }
        else 
        {
            putc(c, fDoc);
            putc(d, fDoc);
        }
    }
    else if( c == '\''|| c == '"')
        echo_quote(c, doc, fDoc);
    else
        putc(c, fDoc);
}

void incomment(FILE *doc)
{
    int c,d;
     
    c = getc(doc);
    d = getc(doc);

    while(c!='*' || d !='/')
    {
        c =d;
        d = getc(doc);
    }
}

void echo_quote(int c, FILE *doc, FILE *fDoc)
{
    int d;

    putc(c, fDoc);
    
    while((d=getc(doc))!=c)
    {
        putc(d, fDoc);
        
        if(d = '\\')
            putc(getc(doc), fDoc);
    }
    putc(d, fDoc);
}
