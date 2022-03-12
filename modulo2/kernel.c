#include "kernel.h"
extern unsigned int Quantum;
extern PCB *ptrReady, *ptrRunning, *ptrExit;

void schedulingShortTerm(PCB **ptrReady, PCB **ptrRunning, PCB **ptrExit)
{
    unsigned int counterToQuantum = 1;

    PCB *ptrNow = NULL;
    if (*ptrReady != NULL)
    {
        ptrNow = extractFirstPCB(ptrReady);
        while (Quantum >= counterToQuantum && !strcmp("LISTO", ptrNow->status))
        {
            move(0, 0);
            clrtoeol();
            mvprintw(0, 0, "Ejecutando PCB con ID: %d",ptrNow->id);
            refresh();
            executeLine(ptrNow);
            counterToQuantum++;
        }
        if (strcmp("EJECUCION", ptrNow->status))
        {
            sprintf(ptrNow->status, "LISTO");
            insertPCB(ptrNow, ptrReady);
        }
        else if (strcmp("TERMINADO", ptrNow->status))
        {

            insertPCB(ptrNow, ptrExit);
        }
        else if (strcmp("ERROR", ptrNow->status))
        {

            insertPCB(ptrNow, ptrExit);
        }
    }
    else
    {
        move(0, 0);
        clrtoeol();
        mvprintw(0, 0, "Ingrese algun comando");
        refresh();
    }
}

void executeLine(PCB *ptrNow)
{

    int flagStatus = tokenizerPrint(ptrNow->archivo);

    if (flagStatus < 0)
    {
        sprintf(ptrNow->status, "ERROR");
    }
    else if (flagStatus == 0)
    {

        sprintf(ptrNow->status, "LISTO");
    }
    else
    {
        sprintf(ptrNow->status, "TERMINADO");
    }
}
