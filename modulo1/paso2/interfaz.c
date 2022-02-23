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
            //mvprintw(i, 0, "Borrando %d", i);
            refresh();
            napms(DELAY_TIMER);
            args[i] = "\0";
        }
         erase();
        for (int i=0; i < MAX_ARGS; i++)
        {
           
            //mvprintw(i, 0, "Argumentos:%s", args[i]);
            refresh();
            napms(DELAY_TIMER);
            
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
    mvscanw(1,3,"%[^\n]",entrada);
    // elimina el mensaje de la parte superior:
    move(0, 0);
    clrtoeol();
    mvprintw(6,0,"\n\n\n%s\n",entrada);
    refresh();
    *str=entrada;
}
/**
 * @brief Regrea un 1 si hay un teclaso pendiente por capturar. 0 en caso contrario.
 * 
 * @return int 
 */
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
