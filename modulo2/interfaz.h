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
/**
 * @brief   Inicializa la interfaz
 * 
 * @return int Retorna -1 si ocurrio un Error
 */
int initInterface();
/**
 * @brief Remueve la interfaz
 * 
 * @return int Retorna 0 si fue con exito
 */
int removeInterface();
/**
 * @brief Recibe un arreglo de caracteres para escanear una entrada
 * 
 * @param entrada 
 */
void getTextFromCommandLine(char *entrada);
/**
 * @brief Limpia la pantalla apartir de "x" y "y"
 * 
 * @param y 
 * @param x 
 */
void clearLineComandToDown(int y, int x);
/**
 * @brief Ejecuta una linea del PCB
 * 
 * @param ptrNow PCB a ejecutar
 * @return int Retorna una Bandera del Estado en el que se quedó el PCB
 */
int executeLine(PCB *ptrNow);
int commandLine(int *argc,char **arguments);
void commandLinePointer();
void printExecution(PCB *ptrRunning);
void printReady(PCB *ptrReady);
void printExit(PCB *ptrExit);
void printSchedule(PCB *ptrRunning,PCB *ptrReady,PCB *ptrExit);
void makeReadys(int argc,char **arguments);
void killPCB(int argc,char **arguments);
#endif