#include <stdio.h>
#include <stdarg.h>

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
#define	WHITE		7

void textcolor(int attr, int fg, int bg);
int print (const char *format, va_list args);

int infof(const char *format, ...)
{
	va_list args;
	va_start (args, format);
	
	textcolor (BRIGHT, WHITE, HIDDEN);
	printf ("INFO: ");
	textcolor (RESET, WHITE, HIDDEN);

	return print(format,args);

}

int warnf(const char *format, ...)
{
	va_list args;
	va_start (args, format);

	textcolor (BRIGHT, YELLOW, HIDDEN);
	printf ("WARNING: ");
	textcolor (RESET, WHITE, HIDDEN);
	
	return print(format,args);

}

int errorf(const char *format, ...)
{
	va_list args;
	va_start (args, format);

	textcolor (BRIGHT, RED, HIDDEN);
	printf ("ERROR: ");
	textcolor (RESET, WHITE, HIDDEN);
	
	return print(format,args);

}

int panicf(const char *format, ...)
{	
	va_list args;
	va_start (args, format);

  	textcolor (BRIGHT, MAGENTA, HIDDEN);
  	printf ("PANIC: ");
	textcolor (RESET, WHITE, HIDDEN);

	return print(format,args);

}

void textcolor(int attr, int fg, int bg)
{	
	char command[13];

	/* Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}

int print (const char *format, va_list args)
{
	int result;

	result = vprintf (format, args);
	va_end (args);

	return result;
}

