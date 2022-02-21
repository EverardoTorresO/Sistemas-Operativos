
#include "interfaz.h"
#include "interprete.h"
#include "operaciones.h"
#include "default.h"
NUM AX, BX, CX, DX, TMP, PC;
char IR[4];
void clearLineComand(int y, int x)
{
    move(y, x);
    clrtoeol();
}

/* ---------------------------------------------------------------------------------------------------------------------------------
 Regresa:   1 si hay un teclazo pendiente por capturar
            0 en caso contrario
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
        switch (FLAG_TOKEN)
        {
        case 0:
            printf("Linea Vacia: No Execute\n");
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
        mvprintw(++renglon, 0, "%s\n", print);
    }
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
    char *print;
    mvprintw(3, 0, "IR:%s\t\tPC:%d,\tAX:%d,\tBX:%d,\tCX:%d,\tDX:%d\n", "    ", PC, AX, BX, CX, DX);
    tokenizerPrint(archivo);
    return 0;
}
int main(void)
{
    char *entrada;
    char **arguments;

    if (initInterface() == 0)
        printf("An Error Ocurred\n");
    do
    {   
        
        getTextFromTerminal(&entrada);
        instructionInterpreter(entrada, &arguments);
        if (strcmp(arguments[0], "ejecutar") == 0 || strcmp(arguments[0], "Ejecutar") == 0 || strcmp(arguments[0], "x") == 0)
        {
            // Mandar llamar una función que lea el archivo indicado e inicie el interprete
            mvprintw(0, 0, "Realizando acción EJECUTAR");
            executeTokenizer(arguments[1]);
        }
        else if (strcmp(arguments[0], "matar") == 0 || strcmp(arguments[0], "Matar") == 0 || strcmp(arguments[0], "k") == 0)
        {
            mvprintw(0, 0, "Realizando acción MATAR");
        }
        else
        {
            mvprintw(0, 0, "Comando desconocido");
        }

        // elimina lo que está en la linea cuando comienzas a escribir:
        move(1, 1); // Se mueve el cursor a donde está el promt para borrar esa fila
        clrtoeol(); // limpia la linea
        

    } while (strcmp(arguments[0], "salir") != 0 && strcmp(arguments[0], "q") != 0);

    getch();

    removeInterface();
    return 0;
}
