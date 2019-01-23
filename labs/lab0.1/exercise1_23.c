#include<stdio.h>
#include<stdlib.h>

void rdComment(int c, FILE *doc, FILE *fDoc);
void inComment(FILE *doc);
void extComment(int c, FILE *doc, FILE *fDoc);

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
		rdComment(c, document, finalDoc);
	}

    	return 0;
}

void rdComment(int c, FILE *doc, FILE *fDoc)
{
    int d;
    if( c == '/')
 {
        if((d=getc(doc))=='*')
         inComment(doc);
        else if( d == '/')
        {
            putc(c, fDoc);
            rdComment(d, doc, fDoc);
        }
        else 
        {
            putc(c, fDoc);
            putc(d, fDoc);
        }
    }
    else if( c == '\''|| c == '"')
        extComment(c, doc, fDoc);
    else
        putc(c, fDoc);
}

void inComment(FILE *doc)
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

void extComment(int c, FILE *doc, FILE *fDoc)
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
