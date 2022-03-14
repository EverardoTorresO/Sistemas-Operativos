#include "cola.h"

void printPtrPCB(PCB *ptrToInsert)
{
    PCB *ptrAux, *ptr = ptrToInsert;
    printf("Imprimiendo PCB");
    if (ptr != NULL)
    {
        do
        {
            printf("%d ", ptr->id);
            ptrAux = ptr;
            ptr = ptrAux->next;
        } while (ptr != NULL);
    }else{
        printf("La Lista apunta a NULL");
    }
}
PCB *makePCB(unsigned int id, char *archivoNombre)
{
    //printf("Creando PCB");
    PCB *ptr = malloc(sizeof(PCB));
    strcpy(ptr->archivoNombre, archivoNombre);
    ptr->id = id;
    ptr->archivo = fopen(archivoNombre, "r");
    if(ptr->archivo==NULL){
        return NULL;
    }
    ptr->next = NULL;
    sprintf(ptr->IR," ");
    ptr->AX=0;
    ptr->BX=0;
    ptr->CX=0;
    ptr->DX=0;
    ptr->PC=0;
    sprintf(ptr->status,"READY");

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
            // printf("Imprimiendo Queu: %d%s", ptr->id, ptr->archivoNombre);
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
            // printf("Imprimiendo Queu: %d%s", ptr->id, ptr->archivoNombre);
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
            // printf("Imprimiendo Queu: %d%s", ptr->id, ptr->archivoNombre);
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
    printf("Eliminado ID %d",(*pcb)->id);
    free(*pcb);
    printf("Post Eliminacion -> S:%s ID:%d",(*pcb)->archivoNombre,(*pcb)->id)   ;
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
        // printf("Imprimiendo Queu: %d%s", ptr->id, ptr->archivoNombre);
        ptrAux = ptr;
        ptr = ptrAux->next;
        *ptrHead = ptrAux->next;
        ptrAux->next=NULL;
        return ptrAux;
    }
    return NULL;
}

int freeMemoryListPCB(PCB **ptrHead)
{
    printf("Liberando Memoria");
    PCB *ptrAux = NULL, *ptr = *ptrHead;
    if (ptr == NULL)
    {
        printf("La lista es Nula");
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