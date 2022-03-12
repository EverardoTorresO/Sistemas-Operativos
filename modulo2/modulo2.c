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

#include "interfaz.h"
#include "interprete.h"
#include "operaciones.h"
#include "default.h"
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include "cola.h"
#include "kernel.h"
NUM AX, BX, CX, DX, TMP, PC;
char IR[4];
PCB *ptrReady, *ptrRunning, *ptrExit;
int CounterPCBID = 0;
char mensajeWarning[200];
char terminalMesage[100];
unsigned int Quantum = 9;
void resetVar()
{
    AX = 0;
    BX = 0;
    CX = 0;
    DX = 0;
    TMP = 0;
    PC = 0;
}
int kbhit(void)
{
    struct timeval tv;
    fd_set read_fd;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&read_fd);
    FD_SET(0, &read_fd);

    if (select(1, &read_fd, NULL, NULL, &tv) == -1)
        return 0;

    if (FD_ISSET(0, &read_fd))
        return 1;

    return 0;
}
int main(void)
{
    char entrada[100];
    char *arguments[MAX_ARGS];

    if (initInterface() == 0)
        printf("An Error Ocurred\n");
    while (1)
    {
        memset(entrada, '\0', 50); // inicializa a caracter nulo el comando y argumento
        if (kbhit() == 1)
        {

            getTextFromTerminal(entrada);
            if (strlen(entrada) <= 1)
            {
                mvprintw(0, 0, "Cadena Vacia");
            }
            else
            {
                int argc = getArgumentsFrom(entrada, " ", arguments);
                if (strcmp(arguments[0], "ejecutar") == 0 || strcmp(arguments[0], "Ejecutar") == 0 || strcmp(arguments[0], "x") == 0)
                {
                    clearLineComandToDown(2, 0);
                    // Mandar llamar una función que lea el archivo indicado e inicie el interprete
                    sprintf(terminalMesage, "Realizando acción EJECUTAR");
                    mvprintw(0, 0, terminalMesage);
                    // executeTokenizer(arguments[1]); //Modulo1.c
                    if (argc > 1)
                    {
                        PCB *ptrAux = NULL;
                        for (int i = 1; i < argc; i++)
                        {
                            CounterPCBID++;
                            // Se crea pcb por cada archivo, si existe, y se agregan a la cola Ready
                            if ((ptrAux = makePCB(CounterPCBID, arguments[i], mensajeWarning)) != NULL)
                            {
                                insertPCB(ptrAux, &ptrReady);
                                move(0, 0);
                                clrtoeol();
                                sprintf(terminalMesage, "Realizando acción EJECUTAR;Creando el PCB con el ID %d  Archivo: \"%s\"", CounterPCBID, arguments[i]);
                                printw(terminalMesage);
                                refresh();
                                // Second * Seconds
                                usleep(1000000 * DELAY_TIMER);
                                move(0, 0);
                                clrtoeol();
                                refresh();
                            }
                            else
                            {

                                move(0, 0);
                                clrtoeol();
                                sprintf(terminalMesage, "El PCB con el supuesto ID %d, Detecto que el Archivo \"%s\" NO EXISTE", CounterPCBID, arguments[i]);
                                printw(terminalMesage);
                                refresh();
                                // Second * Seconds
                                usleep(1000000 * DELAY_TIMER);
                                move(0, 0);
                                clrtoeol();
                                refresh();
                                CounterPCBID--;
                            }
                        }
                    }
                    //schedulingShortTerm(&ptrReady, &ptrRunning, &ptrExit);
                    // resetVar();//Modulo1.c
                }
                else if (strcmp(arguments[0], "matar") == 0 || strcmp(arguments[0], "Matar") == 0 || strcmp(arguments[0], "k") == 0)
                {
                    mvprintw(0, 0, "Realizando acción MATAR");
                }
                else if (strcmp(arguments[0], "salir") == 0 || strcmp(arguments[0], "q") == 0)
                    break;
                else if (strcmp(arguments[0], "clear") == 0 || strcmp(arguments[0], "c") == 0)
                {
                    clearLineComandToDown(2, 0);
                }
                else
                {
                    mvprintw(0, 0, "Comando desconocido");
                    move(1, 0);
                    clrtoeol();
                    refresh();
                }
            }
            move(1, 0);
            clrtoeol();
            refresh();
        }
        else
        {
            // Quantum
            usleep(1000000*DELAY_TIMER);
            schedulingShortTerm(&ptrReady, &ptrRunning, &ptrExit);
            move(1, 0);
            clrtoeol();
            attron(COLOR_PAIR(1));
            printw("$: ");
            attroff(COLOR_PAIR(1));
            refresh();
        }
    }
    removeInterface();
    return 0;
}
