#include "kernel.h"
extern unsigned int Quantum;
extern PCB *ptrReady, *ptrRunning, *ptrExit;
extern int AX,BX,CX,DX,PC,TMP;
void resetVar()
{
    AX = 0;
    BX = 0;
    CX = 0;
    DX = 0;
    TMP = 0;
    PC = 0;
}
void schedulingShortTerm(PCB **ptrReady_1, PCB **ptrRunning_1, PCB **ptrExit_1)
{

    if ((*ptrRunning_1 = getRunning(ptrReady_1)) != NULL)
    {
        move(0, 0);
        clrtoeol();
        refresh();
        usleep(MILISECOND * DELAY_TIMER);
        executePCBRunning(ptrRunning_1);
    }
    else
    {
        mvprintw(0, 0, "Ingrese Algun Comando: PTC esta de Osioso");
        refresh();
    }
}
PCB *getRunning(PCB **ptrReady_1)
{
    PCB *ptrNow = extractFirstPCB(ptrReady_1);
    return ptrNow;
}
void executePCBRunning(PCB **toRunning)
{
    unsigned int counterToQuantum = 0;
    if (*toRunning != NULL)
    {
        PCB *ptrNow = extractFirstPCB(toRunning);
        if (!strcmp(ptrNow->status,"RUNNING"))
        {
            mvprintw(0,0,"Cargando Contexto");
            refresh();
            usleep(SECOND);
        
            loadContext(ptrNow);
        }
        sprintf(ptrNow->status, "RUNNING");
        while (Quantum > counterToQuantum)
        {
            move(0, 0);
            clrtoeol();
            mvprintw(0, 0, "Ejecutando PCB con ID: %d Archivo: %s", ptrNow->id, ptrNow->archivoNombre);
            refresh();
            executeLine(ptrNow);
            counterToQuantum++;
            move(0,0);
            clrtoeol();
            mvprintw(0,0,"Quantum %d",counterToQuantum);
            refresh();
            usleep(SECOND*1);
            if (counterToQuantum == Quantum)
            {
                saveContext(ptrNow);
                resetVar();
                if (strcmp("RUNNING", ptrNow->status))
                {
                    mvprintw(0,0,"Insertando En Litos");
                    refresh();
                    sprintf(ptrNow->status, "RUNNING");
                    insertPCB(ptrNow, &ptrReady);
                }
                else if (strcmp("END", ptrNow->status))
                {
                
                    insertPCB(ptrNow, &ptrExit);
                }
                else if (strcmp("ERROR", ptrNow->status))
                {
                    
                    insertPCB(ptrNow, &ptrExit);
                }
            }
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
    int flagStatus = tokenizerPrint(ptrNow);

    if (flagStatus == -2)
    {
        sprintf(ptrNow->status, "END");
    }
    else if (flagStatus == -1)
    {
        sprintf(ptrNow->status, "ERROR");
    }
    else if (flagStatus == 0)
    {

        sprintf(ptrNow->status, "READY");
    }
    else if (flagStatus == 1)
    {
        sprintf(ptrNow->status, "RUNNING");
    }
}
void saveContext(PCB *toSave){
    toSave->AX=AX;
    toSave->BX=BX;
    toSave->CX=CX;
    toSave->DX=DX;
    toSave->PC=PC;
}
void loadContext(PCB *toSave){
    mvprintw(5,0,"Cargando Contexto");
    refresh();
    AX=toSave->AX;
    BX=toSave->BX;
    CX=toSave->CX;
    DX=toSave->DX;
    PC=toSave->PC;
}
