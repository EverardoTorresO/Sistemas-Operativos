#ifndef COLA_H_
#define COLA_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char status[50];
    struct PCB *next;
} PCB;

void deletePCB (PCB **pcb);
PCB *makePCB(unsigned int id, char *archivoNombre);
void insertPCB(PCB *ptrToInsert,PCB** ptrHead);
PCB* findPCB(unsigned int id, PCB **ptrHead);
PCB *extractPCB(unsigned int id, PCB **prtTo);
void printPtrPCB(PCB *ptrToInsert);
PCB *extractFirstPCB(PCB **ptrTo);
int freeMemoryListPCB(PCB **ptrHead);

#endif