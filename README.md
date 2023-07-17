# mini-unix-shell-42
Repository for our implementation of the 42 Network's Minishell project. The goal of the project was to create a simple UNIX shell, using Bash as reference. 

## Features
- Redirection and here-document support
- Builtins such as "echo" and "export"
- Environment variables
- Pipes
- A working history
- CTRL signals 

## Usage
### build
Run ```make``` in the project root directory.

### run
Run ```./minishell```


## Tools Used
- GCC (limited to C98 standard)
- Make
- CMake
- Google Test

During development we also used docker to compile our code on Linux, mostly so we could use Valgrind for testing purposes.

## Assignment Limitations
The assigment impose several limitations on us:
- Functions cannot be longer than 25 lines.
- Only 1 global variable allowed in the entire project.
- Has to compile on MacOS Mojave using only GNU Make.
- Limited use of external libraries.
