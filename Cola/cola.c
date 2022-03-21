#include "cola.h"

void printPtrPCB(PCB *ptrToInsert)
{
    PCB *ptrAux, *ptr = ptrToInsert;
    printf("Imprimiendo PCB\n");
    if (ptr != NULL)
    {
        do
        {
            printf("%d ", ptr->id);
            ptrAux = ptr;
            ptr = ptrAux->next;
        } while (ptr != NULL);
    }else{
        printf("La Lista apunta a NULL\n");
    }
}
PCB *makePCB(unsigned int id, char *archivoNombre)
{
    printf("Creando PCB\n");
    PCB *ptr = malloc(sizeof(PCB));
    strcpy(ptr->archivoNombre, archivoNombre);
    ptr->id = id;
    ptr->archivo = fopen(archivoNombre, "r");
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
            return ptr;
        }
        return NULL;
    }
}
void deletePCB(PCB **pcb)
{
    printf("Eliminado ID %d\n",(*pcb)->id);
    free(*pcb);
    printf("Post Eliminacion -> S:%s ID:%d\n",(*pcb)->archivoNombre,(*pcb)->id)   ;
    *pcb = NULL;

}

PCB *extractFirstPCB(PCB **ptrHead)
{

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
        *ptrHead = ptrAux->next;
        return ptrAux;
    }
    return NULL;
}

int freeMemoryListPCB(PCB **ptrHead)
{
    printf("Liberando Memoria\n");
    PCB *ptrAux = NULL, *ptr = *ptrHead;
    if (ptr == NULL)
    {
        printf("La lista es Nula\n");
        return -1;
    }
    else
    {

        do
        {
            ptrAux = ptr;
            *ptrHead = ptr;
            ptr = ptrAux->next;
            deletePCB(ptrHead);

            // ptrAux = NULL;


        } while (ptr != NULL);
    }
    return 0;
}