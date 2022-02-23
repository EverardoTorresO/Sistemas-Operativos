
/**
 * @brief Se compila gcc interprete.c operaciones.c paso1.c -o paso1.o
 * 
 */
char IR[4];
#include "default.h"
#include "operaciones.h"
#include "interprete.h"
NUM AX, BX, CX, DX, TMP, PC;

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {

        // printf("%s\n", argv[i]);
        FILE *archivo = fopen(argv[i], "r");
        if (archivo == NULL)
        {
            printf("Error en los argumentos\n");
            //
        }

        tokenizer(archivo);
        // freeMemory(&ptrList);
        /*     */
        printf("_______________________________________________________________\n");
        printf("\tFin de La Ejecucion del Archivo %s\n", argv[0]);
        printf("_______________________________________________________________\n");
    }

    return 0;
}