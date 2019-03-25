# Lab 3.2 - Progress Notifier with Signals

For this laboratory we were assigned to encode a file with a base 64 algorithm, and using signal handlers to catch the 'SIGINFO', and 'SIGINT' then displayiing the current progress.

Implement a program for encoding and decoding files by using the `Base64` [algorithm](https://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64).
You're free to copy from  previous link's implementation (don't forget to reference to the author's page), the interesting part will be the implementation of signal handlers for progress status.

Add one or multiple signal handlers to catch the `SIGINFO` and `SIGINT`. Once a signal is catched, your program should dislay the current progress of the encoding or deconding tasks.

You will need the proper mechanisms for tracking the progress of any encoding/decoding task. You program must support plain text input files.

Encoding
--------
```
./base64 --encode input.txt
```
Your program should generate a new `encoded.txt` file with the result.

Decoding
--------
```
./base64 --decode encoded.txt
```
Your program will generate a `decoded.txt` file witg the result.

How to test?
------------
- Get process ID
```
ps aux | grep base64
```

- Send the signals
```
kill -SIGINT <PID>
kill -SIGINFO <PID>
```


Test files
----------
- [vgilante.txt](http://textfiles.com/stories/vgilante.txt)
- [sick-kid.txt](http://textfiles.com/stories/sick-kid.txt)
- [aesop11.txt](http://textfiles.com/stories/aesop11.txt)

General Requirements and Considerations
---------------------------------------
- Use the logger that was done on [lab2.4](https://github.com/CodersSquad/ap-labs/tree/master/labs/lab2.4).
- Use the `base64.c` file for implementing the lab's general flow.
- Use the `Makefile` for compilation.
- Update `README.md` with the proper steps for building and running your code.
- Don't forget to handle errors properly.
- Coding best practices implementation will be also considered.

# How to run

To run the program the user simply needs to do the following. first he has to do a 'make' in ordre to compile the code. then

```
#Use the following to encode.
./base64 --encode input.txt

#Use the following to decode.
./base64 --decode encoded.txt
```

