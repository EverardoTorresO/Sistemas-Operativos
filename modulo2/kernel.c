#include "kernel.h"

extern unsigned int Quantum, counterToQuantum;
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

void schedulingShortTerm(PCB **ptrReady_1, PCB **ptrRunning_1, PCB **ptrExit_1)
{
    if (*ptrRunning_1 == NULL)
    {
        if ((*ptrRunning_1 = getRunning(&ptrReady)) != NULL)
        {
            move(0, 0);
            clrtoeol();
            refresh();
            executePCBRunning(ptrRunning_1);
        }
        else
        {
            mvprintw(0, 0, "Ingrese Algun Comando: PTC esta de Osioso");
            refresh();
        }
    }
    else
    {
        executePCBRunning(ptrRunning_1);
    }
}
PCB *getRunning(PCB **ptrReady_1)
{
    PCB *ptrNow = extractFirstPCB(ptrReady_1);
    return ptrNow;
}
int executePCBRunning(PCB **toRunning)
{

    if (*toRunning != NULL)
    {
        PCB *ptrNow = extractFirstPCB(toRunning);
        if (!strcmp(ptrNow->status, "WAITING"))
        {
            mvprintw(0, 0, "Cargando Contexto");
            refresh();
            loadContext(ptrNow);
        }
        else if (!strcmp(ptrNow->status, "KILLED"))
        {
            insertPCB(ptrNow, &ptrExit);
            counterToQuantum=0;
            return 0;
        }
        else if (!strcmp(ptrNow->status, "READY"))
        {
            sprintf(ptrNow->status, "RUNNING");
        }
        else if (!strcmp(ptrNow->status, "FINISHED"))
        {
            insertPCB(ptrNow, &ptrExit);
            counterToQuantum=0;
            return 0;
        }
        else if (!strcmp(ptrNow->status, "ERROR"))
        {
            insertPCB(ptrNow, &ptrExit);
            counterToQuantum=0;
            return 0;
        }

        if (Quantum > counterToQuantum && ((0 == strcmp(ptrNow->status, "WAITING")) || (0 == strcmp(ptrNow->status, "RUNNING"))))
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
            mvprintw(2, 0, "flagPCB %d, quantum %d", flagPCB, counterToQuantum);
            refresh();
            switch (flagPCB)
            {
            case RUNNING:
                mvprintw(0, 0, "Insertando En LISTOS");
                refresh();
                if (counterToQuantum < Quantum)
                {
                    sprintf(ptrNow->status, "RUNNING");
                    insertPCB(ptrNow, &ptrRunning);
                }
                else if (counterToQuantum == Quantum)
                {
                    sprintf(ptrNow->status, "READY");
                    insertPCB(ptrNow, &ptrReady);
                    counterToQuantum = 0;
                }
                break;
            case END:
                mvprintw(0, 0, "Insertando En Terminados");
                refresh();
                usleep(SECOND);
                sprintf(ptrNow->status, "FINISHED");
                insertPCB(ptrNow, &ptrExit);
                counterToQuantum = 0;
                break;
            case WAITING:
                sprintf(ptrNow->status, "READY");
                insertPCB(ptrNow, &ptrReady);
                break;
            case ERROR:
                sprintf(ptrNow->status, "ERROR");
                fclose(ptrNow->archivo);
                insertPCB(ptrNow, &ptrExit);
                counterToQuantum=0;
                break;
            case READY:
                sprintf(ptrNow->status, "READY");
                insertPCB(ptrNow, &ptrReady);
                break;
            case SUCCESS:
                refresh();
                if (counterToQuantum < Quantum)
                {
                    sprintf(ptrNow->status, "RUNNING");
                    insertPCB(ptrNow, &ptrRunning);
                }
                else if (counterToQuantum == Quantum)
                {
                    sprintf(ptrNow->status, "READY");
                    insertPCB(ptrNow, &ptrReady);
                    counterToQuantum = 0;
                }
                break;
            case ERROR_CLOSE_FILE:
                mvprintw(0, 0, "Error en el Archivo");
                sprintf(ptrNow->status, "ERROR");
                insertPCB(ptrNow, &ptrExit);
                counterToQuantum = 0;

                refresh();
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
    return 0;
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
    case SUCCESS:
        return SUCCESS;
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
