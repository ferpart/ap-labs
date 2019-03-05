
#define ERROR		1
#define SUCCESS		0

int infof(const char *format, ...);
int warnf(const char *format, ...);
int errorf(const char *format, ...);
int panicf(const char *format, ...);

int main()
{
	infof("Information printing\n");
	warnf("%s printing\n", "Warning");
	errorf("%s printing\n", "Error");
	panicf("%s %s\n", "Panic", "printing");
	
}
