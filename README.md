# Shell Project

This is a simple shell program implemented in C. It provides basic shell functionalities such as executing commands, changing directories, displaying environment variables, and exiting the shell.

## Features

- Supports executing built-in commands (`cd`, `env`, `exit`) and external commands.
- Interactive mode: Shell waits for user input from the command line.
- Non-interactive mode: Shell reads commands from a stream.
- Error handling for command execution and memory allocation failures.
- Displays error messages for command not found or non-zero exit status.
- Supports changing directories (`cd` command).
- Displays environment variables (`env` command).
- Allows the user to exit the shell (`exit` command).

## Usage

To compile the shell program, use the provided Makefile:

```bash
make
```
