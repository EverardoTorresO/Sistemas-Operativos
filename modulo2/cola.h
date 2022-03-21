#ifndef COLA_H_
#define COLA_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * @brief Estructura PCB
 * @param id ID del PCB
 * @param archivoNombre Nombre del archivo del PCB
 * @param PC PC del PCB en ejecución
 * @param AX  Registro
 * @param BX  Registrp
 * @param CX  Registro
 * @param DX  Registro
 * @param IR  Linea que debe de ejecutar el PCB
 * @param status Status del PCB actualmente
 * @param next Siguiente PCB en la cola
 */
typedef struct PCB
{
    unsigned int id;
    char archivoNombre[50];
    FILE *archivo;
    unsigned int PC;
    int AX;
    int BX;
    int CX;
    int DX;
    char IR[25];
    char status[50];
    struct PCB *next;
} PCB;
/**Punteros a las lista Listos, Ejecutados y Terminados*/
extern PCB *ptrReady,*ptrRunning,*ptrExit;
/**
 * @brief Elimina el PCB que recibe
 * 
 * @param pcb Brindar la memoria (&pointer)  del PCB *pointer.
 */
void deletePCB (PCB **pcb);
/**
 * @brief Crea un PCB
 * 
 * @param id El ID que recibira ese PCB
 * @param archivoNombre El nombre del archivo de dicho PCB
 * @return PCB* Retorna un apuntador a una estructura PCB
 */
PCB *makePCB(unsigned int id, char *archivoNombre);
/**
 * @brief Inserta un PCB a la lista ptrHead
 * 
 * @param ptrToInsert El PCB* a insertar
 * @param ptrHead La lista a la que vamos a insertar ptrToInsert
 */
void insertPCB(PCB *ptrToInsert,PCB** ptrHead);
/**
 * @brief Busca un PCB acorde al id y lo extrae
 * 
 * @param id Es el argumento a buscar en la lista &ptrHead
 * @param ptrHead es la Lista en la que vamos a buscar tiene que ser &ptrHead de un PCB *ptrHead
 * @return PCB* Es el PCB localizado y extraido de la lista.
 */
PCB* findPCB(unsigned int id, PCB **ptrHead);
/**
 * @brief Función que imprime con puros printf la lista de PCB, usado en mainCola
 * 
 * @param ptrToInsert Lista a imprimir
 */
void printPtrPCB(PCB *ptrToInsert);
/**
 * @brief Extrae el primer PCB de la lista ptrTo
 * 
 * @param ptrTo La lista extraer
 * @return PCB* El primer PCB de la lista
 */
PCB *extractFirstPCB(PCB **ptrTo);
/**
 * @brief Borra la memoria de la lista ptrHead
 * 
 * @param ptrHead se brinda el parametro &ptrHead del PCB *ptrHead;
 * @return int Retorna -1 si hubo un error y 0 si se realizo correctamente.
 */
int freeMemoryListPCB(PCB **ptrHead);

#endif