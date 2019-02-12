# Lab 1.2 - PTY/TTY Broadcaster

## Within this lab, the assignment is to create a broadcster like the *`wall`* command. Following the next instructions taken from: [here](https://github.com/CodersSquad/ap-labs/tree/master/labs/lab1.2 "Lab 1.2 - PTY/TTY Broadcaster by obedmr")

### These are the instructions: 

Develop a program in C that will serve as a Broadcaster of custom messages for all connected users in your Linux machine. For
 example, if you have 5 ssh-connected users, you should be able to send a message to all users' terminals with a single
 command.

## How to run

For the user to run the program it first needs to be compiled, and then ran adding arguments shown in the following manner:

```
make

./broadcaster.c message

```

The user can write whatever he wants, and it will be sent to all tty (including working one for confirmation).

The following image is an example of the program executing in the original console and 2 ssh connected consoles:
![alt-text](https://github.com/ferpart/ap-labs/blob/master/labs/lab1.2/img/broadcasterExample.png "Testing of program ran on multiple virtual consoles.")
