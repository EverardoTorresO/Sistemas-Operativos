#include "default.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cola.h"
extern NUM AX,BX,CX,DX,TMP,PC;
/**
 * @brief Recibe la linea y el PCB y ejecuta la cadena extraida desde el archivo
 * 
 * @param ptrNow 
 * @param cad 
 * @return NUM 
 */
NUM executeTokens(PCB *ptrNow,char*cad);
char*getCopyString( char *str, int a,int b);
int doOperation(char **operation);
int getRegister(char primero[10]);
int getValue(char valor[10]);
/*Funciones del procesador*/
extern int MOV(int a, int b);
/*Funciones del procesador*/
extern int ADD(int a, int b);
/*Funciones del procesador*/
extern int SUB(int a, int b);
/*Funciones del procesador*/
extern int DIV(int a, int b);
/*Funciones del procesador*/
extern int MUL(int a, int b);
/*Funciones del procesador*/
extern int INC(int a);
/*Funciones del procesador*/
extern int DEC(int a);
/*Funciones del procesador*/
extern void printSchedule(PCB *ptrRunning,PCB *ptrReady,PCB *ptrExit);