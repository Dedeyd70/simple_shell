SIMPLE SHELL TEAM PROJECT DATED 14TH JUNE 2023

DESCRIPTION
OurShell is a command line interpreter program that we developed as a team. Our goal is to provide a simple and intuitive interface that interacts with users operating system by executing commands and managing files. Whether you are a beginner or an experienced user, OurShell offers a user-friendly envirnoment for performing basic system operations.

There are functions and system calls available for us to use as a team on this project and this is just a few of it.

access (man 2 access)
chdir (man 2 chdir)
close (man 2 close)
closedir (man 3 closedir)
execve (man 2 execve)
exit (man 3 exit)
_exit (man 2 _exit)
fflush (man 3 fflush)
fork (man 2 fork)

PROJECT TASK SUMMARY

TASK 0
Write a beautiful code that passes the Betty checks

TASK 1
Write a UNIX command line interpreter.

Usage: simple_shell

TASK 2
Simple shell 0.1 +

Handle command lines with arguments

TASK 3
Simple shell 0.2 +

Handle the PATH
fork must not be called if the command doesn’t exist.

TASK 4
Simple shell 0.3 +

Implement the exit built-in, that exits the shell
Usage: exit
You don’t have to handle any argument to the built-in exit


COMPLILATION
OurShell would be complied using gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
