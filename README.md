# BrainF*ck Interpreter
This is my biggest project so far! Let's dive into this documentation!

## Table of contents
- [Table of contents](#-table-of-contents)
- [Libraries used](#-libraries-used)
- [How to use it](#-how-to-use-it)
- [Example](##-example)
- [How it works under the hood](#-how-it-works-under-the-hood)

## Libraries used
- <stdio.h>
- <stdlib.h>
- <string.h>
- <stdbool.h>

## How to use it

### Syntax:
- `bf FILENAME.BF -OPTIONS`.
or
- `bf -OPTION` for a single option.

### Options:
- `-t` TRACE MODE: Tracks every single command in logs.txt `INPUT FILE NEEDED`
- `-d` DEBUG MODE: Prints only important commans in terminal (`[` `]` `.` `,` ) `INPUT FILE NEEDED`
-  `-h` get help (if you are reading this you already dont need it).
- `-v` show this program's version.

### Example
I've actually made a hello world program in BF for this one.

1. Compile the `bf.c` file to `bf`.
2. This repo has `helloWorld.bf`, copy its contents or just download it.
3. You should have a `helloWorld.bf` file with BF code.
4. Open the terminal in this directory.
5. Enter `bf helloWorld.bf`
6. It should exactly print "`Hello, World!`".

You can try to add `-d` or `-t` at the end to see exactly what is happening.

## How it works under the hood
This is the most interesting part here. I will talk about how It works.

First, some BF interpreter info:
| Info | Count |
| :--- | ---: |
| Cell count | 29999 |
| Cell size | 255|
| Max program size | 1024 |

This executable automatically creates a blank `logs.txt` file. If `-t` is used (TRACE MODE), it will have logs of every single command.

Most of the work is done in the `for (int i = 0; i < programLen; i++)` loop.
I use this `ptr` integer variable as the pointer, and `stack[]` as the cell array.

---

Implementing `+` and `-` was pretty straightforward, `<` and `>` too. They just increment the `ptr` or `stack[ptr]` and loop around if needed.
The `,` is still in beta, it asks the user to enter a single character in the terminal.

And then, the loop functions, `[` and `]` were hardest to code by far! The solution uses a `depth` integer variable that is running through nested loops.

Of course, there are some other smaller things like program options, error handling and etc. But I am not going to go through them. This is of my first C projects ever, so don't judge harshly. I did this only for fun :3

# Thanks for reading this :)
