#include "cola.h"
PCB *ptrReady, ptrRunning, ptrExit;
int main()
{
    for (int i = 0; i < 13; i++)
    {
        char obj[5];
        sprintf(obj,"%d", i);
        insertPCB(makePCB(i, obj), &ptrReady);
    }

    printPtrPCB(ptrReady);
    
    PCB *extracted = extractFirstPCB(&ptrReady); //--
    printf("\n");
    printPtrPCB(ptrReady);
    printf("\n");
    printf("Nodo extraido %d\n",extracted->id);

    PCB *extracted2 = extractFirstPCB(&ptrReady); //--
    printf("\n");
    printPtrPCB(ptrReady);
    printf("\n");
    printf("Nodo extraido %d\n",extracted2->id);
    
    if(freeMemoryListPCB(&ptrReady)==-1)
        printf("La lista es Nula\n");
    printf("\n");
    printPtrPCB(ptrReady);
    printf("\n");


    return 0;
}