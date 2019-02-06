all: main.c
	@gcc -c -w str-main.c -o str-main.o
	@gcc -c -w strlib.c -o strlib.o
	@gcc str-main.o strlib.o -o str-final.o

clean:
	@$(RM) strlib.o str-main.o str-final.o
