/**
 * @file modulo1.c
 * @author José Everardo Torres Orozco & Octavio Corona Hernandez
 * @brief Es un mini interpete de instrucciones asm, acorde como vienen en los archivos instrucciones.asm error*.asm
 * @version 0.1
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "default.h"
char mensajeWarning[MAX_TERMINAL_STRING];
char terminalMesage[MAX_TERMINAL_STRING];
NUM AX, BX, CX, DX, TMP, PC;
char IR[4];
#include "cola.h"
PCB *ptrReady, *ptrRunning, *ptrExit;
unsigned int CounterPCBID = 0;

#include "interfaz.h"
#include "interprete.h"
#include "operaciones.h"
#include <unistd.h>
#include <termios.h>
#include <unistd.h>

#include "kernel.h"

unsigned int Quantum = 3,counterToQuantum;

int main(void)
{

    if (initInterface() == 0)
        printf("An Error Ocurred");
    while (1)
    {
        if (kbhit() == 1)
        {
            commandLinePointer();
            char *arguments[MAX_ARGS];
            int argc;

            switch (commandLine(&argc, arguments))
            {
            case QUIT:
                freeMemoryListPCB(&ptrReady);
                freeMemoryListPCB(&ptrRunning);
                freeMemoryListPCB(&ptrExit);
                removeInterface();
                return 0;
            case CREATE:
                makeReadys(argc, arguments);
                break;

            case KILL:
                killPCB(argc, arguments);

                break;
            }
        }
        else
        {
            schedulingShortTerm(&ptrReady, &ptrRunning, &ptrExit);
            commandLinePointer();
            printSchedule(ptrRunning, ptrReady, ptrExit);
            usleep(MILISECOND * DELAY_TIMER);
        }
    }
    freeMemoryListPCB(&ptrReady);
    freeMemoryListPCB(&ptrRunning);
    freeMemoryListPCB(&ptrExit);
    removeInterface();

    return 0;
}
