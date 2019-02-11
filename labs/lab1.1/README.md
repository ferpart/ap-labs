# Lab 1.1 - mycat

The overall task for this assignment is to write a new version of the cat command using the following specifications.

* Rewrite the cat.c program by using `read`, `write`, `open` and close instead of their library equivalents.
* Generate a report with performance metrics between the existing `cat.c` and your `mycat.c`. The format of the report is free, you can add charts or whatever helps to understand the speed of both approaches.
* Update the `README.md` file with instructions about how to compile and execute your program.

## Usage

To use mycat, the user has to do the following.

```
make

./mycat file
```

**A testing file named *`largefile`* has been added for testing purposes**

As for the statistics of the running of my program, it appears that mycat is 50% slower than the original cat in my implementation. 

The following screenshots show the comparisson between cat and my cat:

### This is cat ran using *`time cat largefile`* 
![alt-text](https://github.com/ferpart/ap-labs/blob/master/labs/lab1.1/img/cat.png "Original cat execution time on largefile file")

### This is mycat ran using *`time ./mycat largefile`*

![alt-text](https://github.com/ferpart/ap-labs/blob/master/labs/lab1.1/img/mycat.png "My cat execution time on largefile file") 

Overall even though my implementation of the cat code is slower than the original cat for the specific file that was tested, there may be cases in which my code may run faster than the original implementation of cat. 
