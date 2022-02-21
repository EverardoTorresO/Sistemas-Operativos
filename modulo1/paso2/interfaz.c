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
}
void instructionInterpreter( char *entrada, char ***argumentos)
{
    char **args;
    move(5, 5);
    char*orig=malloc(strlen(entrada)+1);
    strcpy(orig,entrada);
    clrtoeol();
    int num = 0;
    int i = 0;
    char *token = strtok(orig, " ");
    args[i] = token;
    // loop through the string to extract all other tokens
    while (token != NULL)
    {
        token = strtok(NULL, " ");
        args[++i] = token;
    }
    if (i < MAX_ARGS - 1)
    {
        for (; i < MAX_ARGS; i++)
        {
            mvprintw(i, 0, "Borrando %d", i);
            refresh();
            napms(1000);
            args[i] = "\0";
        }
         erase();
        for (int i=0; i < MAX_ARGS; i++)
        {
           
            mvprintw(i, 0, "Argumentos:%s", args[i]);
            refresh();
            napms(1000);
            
        }
    }
    refresh();
    *argumentos = args;
}

void getTextFromTerminal(char **str)
{
    nocbreak();
    char *entrada = malloc(sizeof(char) * MAX_TERMINAL_STRING);
    move(1, 0);
    attron(COLOR_PAIR(1));
    printw("$: ");
    attroff(COLOR_PAIR(1));
    refresh();

    move(1, 0);
 /*    char ch;
    int i = 0;
    while ((ch = getch()) != '\n' && i < MAX_TERMINAL_STRING)
    {
        entrada[i] = ch;
        i++;
    } */
    mvscanw(1,1,"%[^\n]",entrada);
    // elimina el mensaje de la parte superior:
    move(0, 0);
    clrtoeol();
    mvprintw(6,0,"\n\n\n%s\n",entrada);
    refresh();
    *str=entrada;
}
