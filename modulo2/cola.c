#include "cola.h"

void printPtrPCB(PCB *ptrToInsert)
{
    PCB *ptrAux, *ptr = ptrToInsert;

    if (ptr != NULL)
    {
        do
        {
            printf("\nImprimiendo Queu: %d\n%s\n", ptr->id, ptr->archivoNombre);
            ptrAux = ptr;
            ptr = ptrAux->next;
        } while (ptr != NULL);
    }
}
PCB *makePCB(unsigned int id, char *archivoNombre, char *mensaje)
{
    //printf("Creando PCB\n");
    PCB *ptr = malloc(sizeof(PCB));
    if (ptr == NULL)
    {
        sprintf(mensaje, "Memoria Ocupada\n");
        return NULL;
    }
    ptr->archivo = fopen(archivoNombre, "r");
    if (ptr->archivo == NULL)
    {
        strcat(mensaje, "No Existe el Archivo\n");
        return NULL;
    }
    strcpy(ptr->archivoNombre, archivoNombre);
    ptr->id = id;
    sprintf(ptr->status,"LISTO");
    ptr->next = NULL;
    return ptr;
}
void insertPCB(PCB *toInsert, PCB **head)
{
    PCB *ptrAux = NULL, *ptr = *head;
    if (*head == NULL)
    {
        *head = toInsert;
    }
    else
    {
        do
        {
            // printf("\nImprimiendo Queu: %d\n%s\n", ptr->id, ptr->archivoNombre);
            ptrAux = ptr;
            ptr = ptrAux->next;
        } while (ptr != NULL);
        ptrAux->next = toInsert;
    }
}
PCB *extractPCB(unsigned int id, PCB **ptrHead)
{
    PCB *ptrAux = NULL, *ptr = *ptrHead, *ptrPrev = NULL;
    if (ptr == NULL)
    {
        return NULL;
    }
    else
    {
        do
        {
            // printf("\nImprimiendo Queu: %d\n%s\n", ptr->id, ptr->archivoNombre);
            ptrAux = ptr;
            ptr = ptrAux->next;
        } while (ptr->id != id && ptr != NULL);
        if (ptr != NULL)
        {
            ptrPrev = ptrAux;
            ptrAux = ptr->next;
            ptrPrev->next = ptrAux;
            return ptr;
        }
        return NULL;
    }
}
PCB *findPCB(unsigned int id, PCB **ptrHead)
{
    PCB *ptrAux = NULL, *ptr = *ptrHead;
    if (ptr == NULL)
    {
        return NULL;
    }
    else
    {
        do
        {
            // printf("\nImprimiendo Queu: %d\n%s\n", ptr->id, ptr->archivoNombre);
            ptrAux = ptr;
            ptr = ptrAux->next;
        } while (ptr->id != id && ptr != NULL);
        if (ptr != NULL)
        {
            return ptr;
        }
        return NULL;
    }
}
void deletePCB(PCB **pcb)
{
    free(*pcb);
}
PCB *extractFirstPCB(PCB **ptrHead){
    
    PCB *ptrAux = NULL, *ptr = *ptrHead;
    if (ptr == NULL)
    {
        return NULL;
    }
    else
    {
    
            // printf("\nImprimiendo Queu: %d\n%s\n", ptr->id, ptr->archivoNombre);
            ptrAux = ptr;
            ptr = ptrAux->next;
            *ptrHead=ptrAux->next;
            return ptrAux;
       
    }
     return NULL;
}
int freeMemoryListPCB(PCB **ptrHead)
{
    PCB *ptrAux = NULL, *ptr = *ptrHead;
    if (ptr == NULL)
    {
        return 0;
    }
    else
    {
        do
        {
            // printf("\nImprimiendo Queu: %d\n%s\n", ptr->id, ptr->archivoNombre);
            ptrAux = ptr;
            ptr = ptrAux->next;
            deletePCB(&ptrAux);
        } while ( ptr != NULL);
    }
    return 0;
}
