#include "default.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cola.h"
extern NUM AX,BX,CX,DX,TMP,PC;
extern char IR[4];


/**
 * @brief Asigna a un Registro el valor en el token 3
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int MOV(int a, int b);
int ADD(int a, int b);
int SUB(int a, int b);
int DIV(int a, int b);
int MUL(int a, int b);
int INC(int a);
int DEC(int a);
void freeMemoryArgs(char***args);

int getArguments(const char *orig, char ***argue,int*operation);
NUM whoToken(char *argv);


/**
 ******************************************************************
 * \brief Extrae palabras de una cadena y las coloca en un array
 *
 * \param orig     Cadena inicial
 * \param delim    Las palabras vendrán delimitadas por uno de los
 *                 caracteres de esta cadena            
 * \param args     Array donde separaremos cada palabra
 * \param max_args Número de palabras como máximo a extraer (tamaño
 *                 del array)
 *
 * \return Número de palabras extraídas. (max_args+1) si en la
 *         cadena hay más de max_args palabras.
 *
 ******************************************************************/
int getArgumentsFrom(char *orig, char *delim, char *args[]);
/**Funciones externas ajenas a este documento**/
extern void saveContext(PCB *ptr);