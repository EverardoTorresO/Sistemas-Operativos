#include "kernel.h"
extern unsigned int Quantum;
extern PCB *ptrReady, *ptrRunning, *ptrExit;
extern int AX, BX, CX, DX, PC, TMP;
void resetVar()
{
    AX = 0;
    BX = 0;
    CX = 0;
    DX = 0;
    TMP = 0;
    PC = 0;
}
void executePCBExit(PCB **ptrTo)
{
    if (ptrTo != NULL)
    {
    }
}
void schedulingShortTerm(PCB **ptrReady_1, PCB **ptrRunning_1, PCB **ptrExit_1)
{

    if ((*ptrRunning_1 = getRunning(ptrReady_1)) != NULL)
    {
        move(0, 0);
        clrtoeol();
        refresh();
        executePCBRunning(ptrRunning_1);
    }
    else
    {
        executePCBExit(ptrExit_1);
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
        if (!strcmp(ptrNow->status, "WAITING"))
        {
            mvprintw(0, 0, "Cargando Contexto");
            refresh();
            loadContext(ptrNow);
        }
        sprintf(ptrNow->status, "RUNNING");
        while (Quantum > counterToQuantum && ((0 == strcmp(ptrNow->status, "WAITING")) || (0 == strcmp(ptrNow->status, "RUNNING"))))
        {
            move(0, 0);
            clrtoeol();
            mvprintw(0, 0, "PCB con ID: %d Archivo: %s", ptrNow->id, ptrNow->archivoNombre);
            refresh();
            commandLinePointer();
            loadContext(ptrNow);
            int flagPCB = executeIR(ptrNow);
            printSchedule(ptrRunning, ptrReady, ptrExit);
            saveContext(ptrNow);
            counterToQuantum++;
            move(2, 0);
            clrtoeol();
            mvprintw(2, 0, "flagPCB %d", flagPCB);
            refresh();
            switch (flagPCB)
            {
            case RUNNING:
                mvprintw(0, 0, "Insertando En LISTOS");
                refresh();
                sprintf(ptrNow->status, "RUNNING");
                if (counterToQuantum == Quantum)
                    insertPCB(ptrNow, &ptrReady);
                break;
            case END:
                mvprintw(0, 0, "Insertando En LISTOS");
                refresh();
                sprintf(ptrNow->status, "FINISHED");
                insertPCB(ptrNow, &ptrExit);
                break;
            case WAITING:
                break;
            case ERROR:
                sprintf(ptrNow->status, "ERROR");
                insertPCB(ptrNow, &ptrExit);
                break;
            case READY:
                break;
            case SUCCES:
                refresh();
                if (counterToQuantum == Quantum)
                    insertPCB(ptrNow, &ptrReady);
            default:
                resetVar();
                break;
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
int executeIR(PCB *ptrNow)
{
    int flagStatus = executeLine(ptrNow);
    move(2, 0);
    clrtoeol();
    mvprintw(2, 0, "FlagStatus %d", flagStatus);
    refresh();
    switch (flagStatus)
    {
    case EMPTY_IR:
        return ERROR;
        return EMPTY_IR;
    case BAD_REGISTER:
        return ERROR;
        return BAD_REGISTER;
    case END:
        return END;
    case DIVIDE_BY_CERO:
        return ERROR;
        return DIVIDE_BY_CERO;
    case BAD_INSTRUCTION:
        return ERROR;
        return BAD_INSTRUCTION;
    case SUCCES:
        return SUCCES;
    case ERROR_ARGUMENTS:
        return ERROR;
        return ERROR_ARGUMENTS;
    }
    return flagStatus;
}
void saveContext(PCB *toSave)
{
    toSave->AX = AX;
    toSave->BX = BX;
    toSave->CX = CX;
    toSave->DX = DX;
    toSave->PC = PC;
}
void loadContext(PCB *toSave)
{
    AX = toSave->AX;
    BX = toSave->BX;
    CX = toSave->CX;
    DX = toSave->DX;
    PC = toSave->PC;
}
