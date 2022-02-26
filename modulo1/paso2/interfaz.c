#include "interfaz.h"
#include "default.h"
#include <string.h>

int initInterface()
{

    initscr();
    cbreak();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
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
    printf("%s",entrada);
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

void getTextFromTerminal(char **str)
{
    char *entrada = malloc(sizeof(char) * MAX_TERMINAL_STRING);
    move(1, 0);
    attron(COLOR_PAIR(1));
    printw("$: ");
    attroff(COLOR_PAIR(1));
    refresh();
    move(1, 0);
    mvscanw(1, 3, "%[^\n]", entrada);
    move(0, 0);
    clrtoeol();
    refresh();
    *str = entrada;
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

int tokenizerPrint(FILE *Archivo)
{
    int FLAG_TOKEN = 0;
    char *print = malloc(100);
    sprintf(print, "IR:%s\t\tPC:%d,\tAX:%d,\tBX:%d,\tCX:%d,\tDX:%d\n", "    ", PC, AX, BX, CX, DX);
    mvprintw(2, 0, "%s\n", print);
    char str[30];
    int renglon = 3;
    while (fgets(str, sizeof(str), Archivo) != NULL)
    {
        int len = strlen(str);
        // Verificamos si el último caracter es un salto de línea
        if (str[len - 1] == '\n')
            // Eliminamos el salto de línea
            str[len - 1] = '\0';

        FLAG_TOKEN = executeToken(&print, str);
        fflush(stdout);
        mvprintw(++renglon, 0, "%s\n", print);
        switch (FLAG_TOKEN)
        {
        case 0:
            printf("Linea Vacia: No Execute\n");
            return -1;
            break;
        case 1:
            move(++renglon, 0);
            printw("BAD REGISTER\n");
            refresh();
            return -1;
        case 2:
            move(++renglon, 0);
            printw("END\n");
            refresh();
            return -2;
        case 3:
            move(++renglon, 0);
            printw("Divide By Cero\n");
            refresh();
            return -2;
            break;
        case 4:
            move(++renglon, 0);
            printw("BAD INSTRUCTION\n");
            refresh();
            return -1;
            break;
        case 5:
            move(++renglon, 0);
            printw("Succes\n");
            break;
        }
        
    }
    return 0;
}
int executeTokenizer(char *cadArchivo)
{
    move(3, 0);
    clrtoeol();
    refresh();
    // printf("%s\n", argv[i]);
    FILE *archivo = fopen(cadArchivo, "r");
    if (archivo == NULL)
    {
        mvprintw(3, 0, "Error en los argumentos %s\n", cadArchivo);
        refresh();
        return -1;
    }
    mvprintw(3, 0, "IR:%s\t\tPC:%d,\tAX:%d,\tBX:%d,\tCX:%d,\tDX:%d\n", "    ", PC, AX, BX, CX, DX);
    
    return tokenizerPrint(archivo);;
}
