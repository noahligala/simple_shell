# Simple Shell Project

## Table of Contents

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

<code>
```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
</code>

### Non-Interactive Mode
<code>
	$ echo "/bin/ls" | ./hsh
	hsh main.c shell.c
</code>
