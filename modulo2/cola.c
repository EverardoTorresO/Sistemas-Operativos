#include "cola.h"
#include "default.h"
#include "interfaz.h"
extern char warningMessage[MAX_TERMINAL_STRING];
extern char terminalMessage[MAX_TERMINAL_STRING];

extern char IR[4];
extern PCB *ptrReady, *ptrRunning, *ptrExit;
extern unsigned int CounterPCBID;
void printPtrPCB(PCB *ptrToInsert)
{
    PCB *ptrAux, *ptr = ptrToInsert;
    // printf("Imprimiendo PCB\n");
    if (ptr != NULL)
    {
        do
        {
            // printf("%d \n", ptr->id);
            ptrAux = ptr;
            ptr = ptrAux->next;
        } while (ptr != NULL);
    }
    else
    {
        // printf("La Lista apunta a NULL");
    }
}
PCB *makePCB(unsigned int id, char *archivoNombre)
{
    // printf("Creando PCB\n");
    PCB *ptr = malloc(sizeof(PCB));
    strcpy(ptr->archivoNombre, archivoNombre);
    ptr->id = id;
    ptr->archivo = fopen(archivoNombre, "r");
    if (ptr->archivo == NULL)
    {
        free(ptr);
        return NULL;
    }
    ptr->next = NULL;
    sprintf(ptr->IR, " ");
    ptr->AX = 0;
    ptr->BX = 0;
    ptr->CX = 0;
    ptr->DX = 0;
    ptr->PC = 0;
    sprintf(ptr->status, "READY");

    return ptr;
}
void insertPCB(PCB *toInsert, PCB **head)
{
    PCB *ptrAux = NULL, *ptr = *head;
    if (*head == NULL && toInsert != NULL)
    {
        toInsert->next = NULL;
        *head = toInsert;
    }
    else if (*head != NULL)
    {
        do
        {
            // printf("Imprimiendo Queu: %d%s\n", ptr->id, ptr->archivoNombre);
            ptrAux = ptr;
            ptr = ptrAux->next;
        } while (ptr != NULL);
        ptrAux->next = toInsert;
    }
}
PCB *extractPCB(unsigned int id, PCB **ptrHead)
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
            // printf("Imprimiendo Queu: %d%s", ptr->id, ptr->archivoNombre);
            ptrAux = ptr;
            ptr = ptrAux->next;
        } while (ptr->id != id && ptr != NULL);
        if (ptr != NULL)
        {
            if (ptr->id == id)
            {
                ptrAux->next = ptr->next;
                ptr->next = NULL;
                return ptr;
            }
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
    else if (ptr->id == id)
    {
        ptrAux = ptr->next;
        ptr->next = NULL;
        *ptrHead = ptrAux;
        return ptr;
    }
    else
    {

        do
        {
            ptrAux = ptr;
            ptr = ptrAux->next;
            if (ptr != NULL)
                if (id == ptr->id)
                {
                    ptrAux->next=ptr->next;
                    ptr->next=NULL;
                    return ptr;
                }
        } while (ptr != NULL);

            return NULL;
    }
    return NULL;
}
void deletePCB(PCB **pcb)
{
    // printf("Eliminado ID %d\n", (*pcb)->id);
    free(*pcb);
    // printf("Post Eliminacion -> S:%s ID:%d\n", (*pcb)->archivoNombre, (*pcb)->id);
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
        // printf("Imprimiendo Queu: %d %s\n", ptr->id, ptr->archivoNombre);
        ptrAux = ptr;
        ptr = ptrAux->next;
        *ptrHead = ptrAux->next;
        ptrAux->next = NULL;
        return ptrAux;
    }
    return NULL;
}

int freeMemoryListPCB(PCB **ptrHead)
{
    // printf("Liberando Memoria\n");
    PCB *ptrAux = NULL, *ptr = *ptrHead;
    if (ptr == NULL)
    {
        // printf("La lista es Nula\n");
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
            //  usleep(SECOND);
            // printSchedule(ptrRunning, ptrReady, ptrExit);
            // ptrAux = NULL;

        } while (ptr != NULL);
    }
    return 0;
}
