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
NUM AX, BX, CX, DX, TMP, PC;
char IR[4];
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
    char *entrada = malloc(sizeof(char) * MAX_TERMINAL_STRING);
    char *arguments[2];

    if (initInterface() == 0)
        printf("An Error Ocurred\n");
    while (1)
    {
        memset(entrada, '\0', 50); // inicializa a caracter nulo el comando y argumento
        if (kbhit() == 1)
        {

            getTextFromTerminal(&entrada);

            sleep(DELAY_TIMER);
            if (strlen(entrada) <=1)
            {
                 mvprintw(0, 0, "Cadena Vacia");
                  
            }
            else
            {
                getArgumentsFrom(entrada, " ", arguments, 5);
                if (strcmp(arguments[0], "ejecutar") == 0 || strcmp(arguments[0], "Ejecutar") == 0 || strcmp(arguments[0], "x") == 0)
                {   
                    clearLineComandToDown(2,0);
                    // Mandar llamar una función que lea el archivo indicado e inicie el interprete
                    mvprintw(0, 0, "Realizando acción EJECUTAR");

                    executeTokenizer(arguments[1]);
                    resetVar();
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
