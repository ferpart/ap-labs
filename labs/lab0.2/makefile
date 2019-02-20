all: main.c
	@gcc -c -w main.c -o main.o
	@gcc -c -w strlib.c -o strlib.o
	@gcc str-main.o strlib.o -o str-final.o

clean:
	@$(RM) strlib.o main.o str-final.o
