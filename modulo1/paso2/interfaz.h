#include <ncurses.h>
#include <stdlib.h>
#define NORMAL_INTERFACE 1

int initInterface();
int removeInterface();
void getTextFromTerminal(char **entrada);
void instructionInterpreter(char *entrada,char***argumentos);
