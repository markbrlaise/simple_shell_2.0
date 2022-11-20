#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAXCOM 1000 //max number of characters to be suported
#define MAXLIST 100 //max number of commands to be supported

//clear the shell using escape sequencies
#define clear() printf("\033[H\033[J")

void init_shell();
int takeInput(char *str);
void execArgs(char **parsed);
void execArgsPiped(char **parsed, char **parsedpipe);
void openHelp();
int ownCmdHandler(char **parsed);
int parsePipe(char *str, char **strpiped);
void parseSpace(char *str, char **parsed);
int processString(char *str, char **parsed, char **parsedpie);
int _strcmp(const char *s1, const char *s2);

#endif /* MAIN_H */

