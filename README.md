# Simple Shell Project

## Description
This is a simple UNIX command interpreter created as part of the Holberton School curriculum. The shell can read and execute commands from standard input or files.

## Features
- Execute commands using their full path (ls)
- Execute commands using PATH environment variable (`ls`)
- Handle command line arguments (`ls -l /tmp`)
- Support for built-in commands:
  - `exit`: Exit the shell
  - `env`: Print the current environment variables
- Handle the End-Of-File condition (Ctrl+D)
- Handle signals (Ctrl+C)

## Requirements
- Compiled on Ubuntu 20.04 LTS using gcc with the options: `-Wall -Werror -Wextra -pedantic -std=gnu89`
- All files end with a new line
- Code follows the Betty style
- No more than 5 functions per file
- All header files are include guarded

## Compilation
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage
### Interactive Mode
```
$ ./hsh
#cisfun$ ls
file1 file2 file3
#cisfun$ exit
$
```

### Non-Interactive Mode
```
$ echo "ls" | ./hsh
file1 file2 file3
$
```

## Files
- shell.c: Main program and shell loop
- executor.c: Functions to execute commands
- parser.c: Functions to parse input
- path.c: Functions to handle PATH
- env_utils.c: Functions to handle environment variables
- builtins.c: Implementation of built-in commands
- shell.h: Header file

## Built-in Commands
- `exit`: Exit the shell
- `env`: Print the current environment variables

## Return Value
The shell returns the exit status of the last command executed, or 0 for successful execution of a built-in command.

## Example
```
$ ./hsh
#cisfun$ ls -l /tmp
total 20
-rw------- 1 user user    0 Apr 21 12:09 config-err-aAMZrR
drwx------ 3 root root 4096 Apr 21 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-colord.service-V7DUzr
drwx------ 3 root root 4096 Apr 21 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-rtkit-daemon.service-ANGvoV
drwx------ 3 root root 4096 Apr 21 12:07 systemd-private-062a0eca7f2a44349733e78cb4abdff4-systemd-timesyncd.service-CdXUtH
-rw-rw-r-- 1 user user    0 Apr 21 12:09 unity_support_test.0
#cisfun$ exit
$
```

## Authors
- Stephane Paton
- Wassef Abdallah

## License
This project is licensed under the terms of the MIT license.