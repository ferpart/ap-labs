CC       = gcc
CFLAGS   = -Wall -pthread
LDFLAGS  =
OBJFILES = logger.o multiplier.o
TARGET   = multiplier

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
