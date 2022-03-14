#include "interfaz.h"
#include "default.h"
#include <string.h>
#include "cola.h"
char terminalMessage[MAX_TERMINAL_STRING];
char warningMessage[MAX_TERMINAL_STRING];
extern unsigned int CounterPCBID;
extern PCB *ptrReady, *ptrRunning, *ptrExit;
int commandLine(char **arguments)
{
    char entrada[100];
    getTextFromCommandLine(entrada);
    if (strlen(entrada) <= 1)
    {
        mvprintw(0, 0, "Cadena Vacia");
    }
    else
    {
        int argc = getArgumentsFrom(entrada, " ", arguments);
        if (strcmp(arguments[0], "ejecutar") == 0 || strcmp(arguments[0], "Ejecutar") == 0 || strcmp(arguments[0], "x") == 0)
        {
            // clearLineComandToDown(2, 0);
            //  Mandar llamar una función que lea el archivo indicado e inicie el interprete
            sprintf(terminalMessage, "Realizando acción EJECUTAR");
            mvprintw(0, 0, terminalMessage);
            // SUCCESSizer(arguments[1]); //Modulo1.c
            if (argc > 1)
            {
                PCB *ptrAux = NULL;
                for (int i = 1; i < argc; i++)
                {
                    CounterPCBID++;
                    // Se crea pcb por cada archivo, si existe, y se agregan a la cola Ready
                    if ((ptrAux = makePCB(CounterPCBID, arguments[i])) != NULL)
                    {
                        insertPCB(ptrAux, &ptrReady);
                        move(0, 0);
                        clrtoeol();
                        sprintf(terminalMessage, "Realizando acción EJECUTAR;Creando el PCB con el ID %d  Archivo: \"%s\"", CounterPCBID, arguments[i]);
                        printw(terminalMessage);
                        refresh();
                        // Second * Seconds
                        move(0, 0);
                        clrtoeol();
                        refresh();
                    }
                    else
                    {

                        move(0, 0);
                        clrtoeol();
                        sprintf(terminalMessage, "El PCB con el supuesto ID %d, Detecto que el Archivo \"%s\" NO EXISTE", CounterPCBID, arguments[i]);
                        printw(terminalMessage);
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
            // schedulingShortTerm(&ptrReady, &ptrRunning, &ptrExit);
            //  resetVar();//Modulo1.c
        }
        else if (strcmp(arguments[0], "matar") == 0 || strcmp(arguments[0], "Matar") == 0 || strcmp(arguments[0], "k") == 0)
        {
            mvprintw(0, 0, "Realizando acción MATAR");
        }
        else if (strcmp(arguments[0], "salir") == 0 || strcmp(arguments[0], "q") == 0)
            return 1;
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
    return 0;
}
int initInterface()
{

    initscr();
    cbreak();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    attrset(A_NORMAL);

    return 1;
}
int removeInterface()
{
    endwin();
    return 0;
}
int instructionInterpreter(char *entrada, char ***argumentos)
{
    char **args = NULL;
    char *orig = malloc(strlen(entrada) + 1);
    strcpy(orig, entrada);
    printf("%s", entrada);
    int i = 0;
    char *token = strtok(orig, " ");
    if (token == NULL)
    {
        return -1;
    }
    args[i] = token;
    // loop through the string to extract all other tokens
    while (token != NULL)
    {
        token = strtok(NULL, " ");
        mvprintw(2, 0, "%s", args[i]);
        refresh();
        args[++i] = token;
    }
    refresh();
    *argumentos = args;
    return 0;
}

void getTextFromCommandLine(char *str)
{

    move(1, 0);
    attron(COLOR_PAIR(1));
    printw("$: ");
    attroff(COLOR_PAIR(1));
    refresh();
    move(1, 0);
    mvscanw(1, 3, "%[^\n]", str);
    move(0, 0);
    clrtoeol();
    refresh();
}
/**
 * @brief Regrea un 1 si hay un teclaso pendiente por capturar. 0 en caso contrario.
 *
 * @return int
 */

void clearLineComandToDown(int y, int x)
{
    for (int i = y; i < getmaxy(stdscr); i++)
    {
        move(i, x);
        clrtoeol();
    }
}

int executeLine(PCB *ptrNow)
{
    FILE *Archivo = ptrNow->archivo;
    int FLAG_TOKEN = 0;
    char str[30];
    if (fgets(str, sizeof(str), Archivo) != NULL)
    {
        int len = strlen(str);
        // Verificamos si el último caracter es un salto de línea
        if (str[len - 1] == '\n')
            str[len - 1] = '\0'; // Eliminamos el salto de línea

        FLAG_TOKEN = executeToken(ptrNow, str);
        refresh();
        usleep(SECOND);
        switch (FLAG_TOKEN)
        {
        case INVALID_ARGUMENTS:
            return INVALID_ARGUMENTS;
        case ERROR_ARGUMENTS:
            return ERROR_ARGUMENTS;
        case 0:
            return EMPTY_IR;
        case 1:
            return BAD_REGISTER;
        case 2:
            return END;
        case 3:
            return DIVIDE_BY_CERO;
        case 4:
            return BAD_INSTRUCTION;
        case SUCCESS:
            return SUCCESS;
        case 6:
            return ERROR_ARGUMENTS;
        }
    }
    return END;
}
void printExecution(PCB *ptrRunning)
{
    attron(COLOR_PAIR(2));
    mvprintw(3, 0, "EJECUCION\n");
    attroff(COLOR_PAIR(2));
    int x = getmaxx(stdscr);
    for (int i = 0; i < x; i++)
    {
        addch('-');
    }
    printw("STATUS \t FileName \t PID \tPC\tIR\t\tAX\tBX\tCX\tDX\n");
    for (int i = 0; i < x; i++)
    {
        addch('-');
    }
    if (ptrRunning != NULL)
        printw("%s\t%s\t\t%d\t%d\t%s\t\t%d\t%d\t%d\t%d\n", ptrRunning->status, ptrRunning->archivoNombre, ptrRunning->id, ptrRunning->PC, ptrRunning->IR, ptrRunning->AX, ptrRunning->BX, ptrRunning->CX, ptrRunning->DX);
    else
        printw("");

    for (int i = 0; i < x; i++)
    {
        addch('-');
    }
}
void printReady(PCB *ptrReady)
{
    attron(COLOR_PAIR(2));
    printw("\nLISTOS\n");
    attroff(COLOR_PAIR(2));
    int x = getmaxx(stdscr);
    for (int i = 0; i < x; i++)
    {
        addch('-');
    }
    printw("STATUS \t FileName \t PID \tPC\tIR\t\tAX\tBX\tCX\tDX\n");
    for (int i = 0; i < x; i++)
    {
        addch('-');
    }
    PCB *ptrAux = NULL, *ptr = ptrReady;
    if (ptr != NULL)
    {
        do
        {
            // printf("Imprimiendo Queu: %d%s", ptr->id, ptr->archivoNombre);
            ptrAux = ptr;
            printw("%s\t%s\t\t%d\t%d\t%s\t\t%d\t%d\t%d\t%d\n", ptrAux->status, ptrAux->archivoNombre, ptrAux->id, ptrAux->PC, ptrAux->IR, ptrAux->AX, ptrAux->BX, ptrAux->CX, ptrAux->DX);
            ptr = ptrAux->next;

        } while (ptr != NULL);
    }
    else
        printw("\n");

    for (int i = 0; i < x; i++)
    {
        addch('-');
    }
}
void printExit(PCB *ptrExit)
{
    attron(COLOR_PAIR(2));
    printw("\nTERMINADOS\n");
    attroff(COLOR_PAIR(2));
    int x = getmaxx(stdscr);
    for (int i = 0; i < x; i++)
    {
        addch('-');
    }
    printw("STATUS \t FileName \t PID \tPC\tIR\t\tAX\tBX\tCX\tDX\n");
    for (int i = 0; i < x; i++)
    {
        addch('-');
    }
    PCB *ptrAux = NULL, *ptr = ptrExit;
    if (ptr != NULL)
    {
        do
        {
            // printf("Imprimiendo Queu: %d%s", ptr->id, ptr->archivoNombre);
            ptrAux = ptr;
            printw("%s\t%s\t\t%d\t%d\t%s\t\t%d\t%d\t%d\t%d\n", ptrAux->status, ptrAux->archivoNombre, ptrAux->id, ptrAux->PC, ptrAux->IR, ptrAux->AX, ptrAux->BX, ptrAux->CX, ptrAux->DX);
            ptr = ptrAux->next;

        } while (ptr != NULL);
    }
    else
        printw("\n");

    for (int i = 0; i < x; i++)
    {
        addch('-');
    }
}
void commandLinePointer(void)
{
    move(1, 0);
    clrtoeol();
    attron(COLOR_PAIR(1));
    printw("$: ");
    attroff(COLOR_PAIR(1));
    refresh();
}
void printSchedule(PCB *ptrRunning, PCB *ptrReady, PCB *ptrExit)
{
    fflush(stdout);
    printExecution(ptrRunning);
    printReady(ptrReady);
    printExit(ptrExit);
    refresh();
}