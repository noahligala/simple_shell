#Simple Shell Project

##Table of Contents

- [Description](#description)
- [Requirements](#requirements)
- [Usage](#usage)
- [Tasks](#tasks)
- [Compilation](#compilation)
- [Testing](#testing)
- [Authors](#authors)
- [GitHub Repository](#github-repository)

## Description

This is a simple UNIX command-line interpreter (shell) project developed in C. The shell is designed to execute commands entered by the user and handle specific requirements outlined in the project prompt.

## Requirements

- The shell should display a prompt and wait for the user to enter a command.
- Commands should be simple, one-word lines, with no arguments.
- The shell should display an error message if an executable is not found and continue to prompt for input.
- The shell should handle errors, including the "end of file" condition (Ctrl+D).
- The shell should not use the PATH to search for executables.
- The shell should implement built-ins, including `exit` and `env`.
- The shell should handle command lines with arguments.
- The shell should handle the PATH and ensure `fork` is not called for non-existing commands.

## Usage

To use the simple shell, compile the program and run it. You can interact with the shell in both interactive and non-interactive modes.

### Interactive Mode


```bash
	$ ./hsh
	($) /bin/ls
	hsh main.c shell.c
	($)
	($) exit
	$
```


### Non-Interactive Mode
	```
	$ echo "/bin/ls" | ./hsh
	hsh main.c shell.c
	```
 ### Tasks
The project consists of several tasks:

Betty would be proud: Ensure that your code follows the Betty style guide.

Simple shell 0.1: Create a basic shell that displays a prompt, accepts one-word commands, and handles errors.

Simple shell 0.2: Extend the shell to handle commands with arguments.

Simple shell 0.3: Implement the PATH and ensure fork is not called for non-existing commands.

Simple shell 0.4: Implement the exit built-in command.

Simple shell 1.0: Implement the env built-in command to display the current environment.

Compilation
To compile the shell, use the following command:

bash
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

### Testing
You can test the shell in both interactive and non-interactive modes. Interactive mode allows you to enter commands directly, while non-interactive mode accepts input from a file or a pipe.

### Authors
This project is a collaborative effort, and the authors are:

<bold>Ligala Noah</bold>
GitHub Repository
You can find the source code for this project on GitHub at GitHub Repository: simple_shell.





