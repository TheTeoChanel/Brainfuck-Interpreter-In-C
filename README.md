
# BrainF*ck Interpreter
This is my biggest project so far! Let's dive into this documentation!

## 1. Table of contents
- [1. Table of contents](#1-table-of-contents)
- [2. What is BrainF*ck?](#2-what-is-brain-f*ck)
- [3. Libraries used](#3-libraries-used)
- [4. How to use it](#4-how-to-use-it)
- [4.1 Syntax](#41-syntax)
- [4.2 Options](#42-options)
- [4.3 Example](#43-example)
- [5. How it works under the hood](#5-how-it-works-under-the-hood)
- [5.1 Known limitations](#51-known-limitations)

## 2. What is BrainF*ck?
BrainF*ck (or BF), is an esolang by Urban Muller. It's a super small programming language that is inspired by the concept of `Turing Machine`.
This language only has 8 commands and everything else is ignored. Here is the syntax:

`+`: Increment value of the current cell by 1.
`-`: Decrement value of the current cell by 1.
`<`: Move the pointer left by 1.
`>`: Move the pointer right by 1.
`.`: Print current cell value using ASCII.
`,`: Ask the user to enter a single character and puts it in the cell.
`[`: If current cell value is 0, it skips the loop.
`]`: If current value is NOT 0, it loops back.

## 3. Libraries used
- <stdio.h>
- <stdlib.h>
- <string.h>
- <stdbool.h>

## 4. How to use it

### 4.1 Syntax:
- `bf FILENAME.BF -OPTIONS`. Single dash means that input file needed.
or
- `bf --OPTION`. Double dashes mean that there is no input file needed.
- 
### 4.2 Options:
- `-trace` TRACE MODE: Tracks every single command and logs it in `logs.txt` `INPUT FILE NEEDED`
- `-debug` DEBUG MODE: Prints only important commands in terminal (`[` `]` `.` `,` ) `INPUT FILE NEEDED`
-  `--help` get help (if you are reading this you already don't need it).
- `--version` show this program's version.

### 4.3 Example
I've actually made a hello world program in BF for this one.

1. Compile the source code `bf.c` into `bf`.
2. Download and put the file `helloWorld.bf` into the same directory as the `bf` executable.
3. Open the terminal in this directory. Enter `./bf helloworld.bf` if you are in UNIX bash terminal. If you are in Windows terminal, enter `bf helloWorld.bf`.

It should exactly print "`Hello, World!`".

You can also add `-debug` or `-trace` at the end to see exactly what is happening.

## 5. How it works under the hood
Now, I will talk about how I coded it.

First, some BF interpreter info:
| Info | Count |
| :--- | ---: |
| Cell count | 29999 |
| Cell size | 0-255|
| Max program size | 1024 |

This executable automatically creates a blank `logs.txt` file. If `-trace` is used (TRACE MODE), it will have logs of every single command.

Most of the work is done in the `for (int i = 0; i < programLen; i++)` loop.
I use this `ptr` integer variable as the pointer, and `stack[]` as the cell array.

---
Implementing `+` and `-` was pretty straightforward, `<` and `>` too. They just increment the `ptr` or `stack[ptr]` and loop around if needed.
The `,` is still in beta, it asks the user to enter a single character in the terminal.

And then, the loop functions `[` and `]` were hardest to code by far! The solution uses a `depth` integer variable that is running through nested loops.

Of course, there are some other smaller things like program options, error handling and etc. But I am not going to go through them. This is one of my first C projects ever, so don't judge harshly. I did this only for fun :3

### 5.1 Known limitations

The `,` command is still in beta. It asks the user for a single character.
No `[` and `]` error handling. If there is not properly closed loops, interpreter will behave unpredictably, please check your BF code.

# Thanks for reading this :)
