## Strings Manipulation Library (Lab 0.2)

For this assignment we've been tasked with making a library for string manipulation following the next instructions: 

* Implement a library for string manipulation strlib.c with the following functions:
```
int strlen(char *str)
*char stradd(char *origin, char *addition)
int strfind(char *origin, char *substr)
´´´
* Call all functions from strlib.c library in a new str-main.c file

* Use the following commands for compilation and linking
´´´
gcc -c str-main.c -o str-main.o
gcc -c strlib.c -o strlib.o
gcc str-main.o strlib.o -o str-final.o
```
* Your program needs to support the following arguments. Check the expected output:
´´´
./str-final.o originalVeryLongString Addition Add
Initial Lenght      : 22
New String          : originalVeryLongStringAddition
SubString was found : yes
```

### How to compile and run the program

To compile the program a make file has been put in the main directory. One just needs to run
´´´
make
```

To run the program, the user needs to do the following command:
´´´
./str-final.o [arg1] [arg2] [arg3]
```

If for some reason the user wants to remove the object files from the directory just run:
´´´
make clean
```


