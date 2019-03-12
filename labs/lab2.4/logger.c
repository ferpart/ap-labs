#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <syslog.h>


#define RESET		0
#define BRIGHT 		1
#define DIM		2
#define UNDERLINE 	3
#define BLINK		4
#define REVERSE		7
#define HIDDEN		8

#define BLACK 		0
#define RED		1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define MAGENTA		5
#define CYAN		6
#define WHITE		7


void textcolor(int attr, int fg, int bg);
int print (const char *format, va_list args, int logType);
int infof(const char *format, ...);

int logging = 0;

int initLogger(char *logType){

	if (strcmp(logType, "syslog")==0)
	{
		infof("Check your %s at /var/log/syslog for syslogs\n", logType);
		logging=1;
		return 0;
	}
	else if(strcmp(logType, "stdout")==0 || strcmp(logType, "")==0)
	{
		logging=0;
		return 0;
	}
	return 1;	
	
}

int infof(const char *format, ...)
{
	va_list args;
	va_start (args, format);
	
	if (logging==0)
	{
	textcolor (BRIGHT, WHITE, HIDDEN);
	printf ("INFO: ");
	textcolor (RESET, WHITE, HIDDEN);
	}

	return print(format,args, 0);
}

int warnf(const char *format, ...)
{
	va_list args;
	va_start (args, format);
	
	if (logging==0)
	{
	textcolor (BRIGHT, YELLOW, HIDDEN);
	printf ("WARNING: ");
	textcolor (RESET, WHITE, HIDDEN);
	}

	return print(format,args, 1);

}

int errorf(const char *format, ...)
{
	va_list args;
	va_start (args, format);
	
	if (logging==0)
	{
	textcolor (BRIGHT, RED, HIDDEN);
	printf ("ERROR: ");
	textcolor (RESET, WHITE, HIDDEN);
	}

	return print(format,args, 2);

}

int panicf(const char *format, ...)
{	
	va_list args;
	va_start (args, format);
	
	if (logging==0)
	{
  	textcolor (BRIGHT, MAGENTA, HIDDEN);
  	printf ("PANIC: ");
	textcolor (RESET, WHITE, HIDDEN);
	}

	return print(format,args, 3);

}

void textcolor(int attr, int fg, int bg)
{	
	char command[13];

	/* Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}

int print (const char *format, va_list args, int logType)
{
	int result = 1;

	if (logging)
	{
		char *editedFormat;
		editedFormat=calloc(strlen(format)+9, sizeof(char));

		editedFormat[strlen(format)+9]='\0';

		switch (logType)
		{
			case 0:
				strcpy(editedFormat, "<info> ");
				strcat(editedFormat, format);
				vsyslog(LOG_USER | LOG_INFO, editedFormat, args);
				break;
			case 1:
				strcpy(editedFormat, "<warn> ");
				strcat(editedFormat, format);
				vsyslog(LOG_USER | LOG_WARNING, editedFormat, args);
				break;
			case 2:
				strcpy(editedFormat, "<error> ");
				strcat(editedFormat, format);
				vsyslog(LOG_USER | LOG_ERR, editedFormat, args);
				break;
			case 3:
				strcpy(editedFormat, "<panic> ");
				strcat(editedFormat, format);
				vsyslog(LOG_USER | LOG_EMERG, editedFormat, args);
				break;
		}
		result=0;		
	}
	else
	{	
		vprintf (format, args);
		result=0;
	}	
	va_end (args);
	return result;
}

