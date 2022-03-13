#ifndef _INTERFAZ_H_
#define _INTERFAZ_H_
#include <ncurses.h>
#include <stdlib.h>
#include <termios.h>
#define NORMAL_INTERFACE 1
#include "interprete.h"
#include "cola.h"
#include "operaciones.h"
extern int PC,AX,BX,CX,DX;
extern char IR[4];
extern unsigned int CounterPCBID;
extern PCB *ptrReady;
int initInterface();
int removeInterface();
void getTextFromCommandLine(char *entrada);
int instructionInterpreter(char *entrada, char ***argumentos);
void clearLineComandToDown(int y, int x);
int executeLine(PCB *ptrNow);
int commandLine(char **arguments);
void commandLinePointer();
void printExecution(PCB *ptrRunning);
void printReady(PCB *ptrReady);
void printExit(PCB *ptrExit);
void printSchedule(PCB *ptrRunning,PCB *ptrReady,PCB *ptrExit);

#endif