#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <signal.h>
#include <termios.h>
#include <signal.h>

#include <sys/wait.h>
#include <sys/types.h>

#define PROMPT "\e[93m$\e[39m "

#define IS_CHILD_PROCESS(PID) (PID == 0)

void execute_system(char**);
void child_process(char*, char**);
void parent_process(pid_t);
int main(int, char**);

#endif /* SHELL_H */
