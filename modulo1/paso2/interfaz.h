#include <ncurses.h>
#include <stdlib.h>
#include <termios.h>
#define NORMAL_INTERFACE 1
#include "interprete.h"

extern int PC,AX,BX,CX,DX;
extern char IR[4];
int initInterface();
int removeInterface();
void getTextFromTerminal(char **entrada);
int instructionInterpreter(char *entrada, char ***argumentos);
void clearLineComandToDown(int y, int x);
int tokenizerPrint(FILE *Archivo);
int executeTokenizer(char *cadArchivo);
