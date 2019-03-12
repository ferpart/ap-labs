int infof(const char *format, ...);
int warnf(const char *format, ...);
int errorf(const char *format, ...);
int panicf(const char *format, ...);
int initLogger (char *logType);

int main()
{
	infof("Information printing\n");
	warnf("%s printing\n", "Warning");
	errorf("%s printing\n", "Error");
	panicf("%s %s\n", "Panic", "printing");

	initLogger("syslog");
	
	infof("Information printing\n");
	warnf("%s printing\n", "Warning");
	errorf("%s printing\n", "Error");
	panicf("%s %s\n", "Panic", "printing");
	
	return 0;
}
