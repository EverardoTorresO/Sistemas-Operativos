#include "cola.h"
PCB *ptrReady=NULL, *ptrRunning=NULL, *ptrExit=NULL;
int main()
{
    for (int i = 0; i < 13; i++)
    {
        char obj[10];
        sprintf(obj,"archivo %d", i);
        insertPCB(makePCB(i, obj), &ptrReady);
    }
    printf("Ready\n");
    printPtrPCB(ptrReady);

    PCB *ptr = findPCB(1,&ptrReady); //--
    printf("ptr\n");
    printPtrPCB(ptr);
        printf("aFTER Ready\n");
    printPtrPCB(ptrReady);
    
    freeMemoryListPCB(&ptrReady);
    printf("\n");
    printPtrPCB(ptrReady);
    printf("\n");


    return 0;
}