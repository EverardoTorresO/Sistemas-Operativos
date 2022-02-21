
#include "interfaz.h"
#include "interprete.h"
#include "operaciones.h"
#include "default.h"
NUM lastAX, lastBX, lastCX, lastDX, lastTMP, PC;
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
void tokenizerPrint(FILE *Archivo)
{   char *print;
    printf("IR:%s\t\tPC:%d,\tAX:%d,\tBX:%d,\tCX:%d,\tDX:%d\n", "    ", PC, lastAX, lastBX, lastCX, lastDX);
    char str[30];
    int i = 1;
    int renglon=5;
    while (fgets(str, sizeof(str), Archivo) != NULL)
    {
        int len = strlen(str);
        // Verificamos si el último caracter es un salto de línea
        if (str[len - 1] == '\n')
            // Eliminamos el salto de línea
            str[len - 1] = '\0';
        if (!executeToken(&print,str,i))
            break;
        mvprintw(renglon,0,print);
        renglon++;
        i++;
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
    mvprintw(3, 0, "IR:%s\t\tPC:%d,\tAX:%d,\tBX:%d,\tCX:%d,\tDX:%d\n", "    ", PC, lastAX, lastBX, lastCX, lastDX);
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
