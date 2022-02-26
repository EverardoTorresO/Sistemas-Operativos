#include "default.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern NUM AX,BX,CX,DX,TMP,PC;
NUM tokenizer(FILE *Archivo);
NUM executeToken(char **str,char*cad);
char*getCopyString( char *str, int a,int b);
int whoOperation(char*cad);
/*Funciones de la biblioteca*/
int doOperation(char **operation);
int getRegister(char primero[10]);
int getValue(char valor[10]);
/*Funciones del procesador*/
extern int MOV(int a, int b);
extern int ADD(int a, int b);
extern int SUB(int a, int b);
extern int DIV(int a, int b);
extern int MUL(int a, int b);
extern int INC(int a);
extern int DEC(int a);