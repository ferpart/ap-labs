##First code challenge

###For this challenge we were assigned the following:

Given a string, find the length of the longest substring without repeating characters.

* Example 1
```
Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 
```

* Example 2
```
Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
```

* Example 3
```
Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. 
Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
```

###How to run/ Basic Description

As the file is made in c, to compile you just need to type the command: 
```
gcc codeChal1.c
./a.out
```

The code recieves a string that has to be typed in the console, and it will check and return the length of the longest substring.

As this is my first time properly using c as a language, the program does
not currently work because of an error that states:
```
*** stack smashing detected ***: <unknown> terminated
Aborted (core dumped)
```
