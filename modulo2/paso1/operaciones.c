#include "operaciones.h"

extern char IR[4];
short int _ERROR_FLAG = 0;

char *getCopyString(char *str, int a, int b)
{
    char *instruction = malloc(sizeof(char) * ((b - a) + 1));
    for (int i = a; i <= b; i++)
    {
        instruction[i] = str[i];
        // printf("copíando caracter: %c", str[i]);
    }
    // printf("cad:%scopy:%s \t%d %d ", str, instruction, a, b);
    return instruction;
}
int getArgumentsFrom(char *orig, char *delim, char *args[])
{
    char *tmp;
    int num = 0;
    /* Reservamos memoria para copiar la candena ... pero la memoria justa */
    char *str = malloc(strlen(orig) + 1);
    strcpy(str, orig);

    /* Extraemos la primera palabra */
    tmp = strtok(str, delim);
    do
    {
        args[num] = tmp; /* Copiamos la dirección de memoria tmp en args[num] */
        num++;

        /* Extraemos la siguiente palabra */
        tmp = strtok(NULL, delim);
    } while (tmp != NULL);
    return num;
}
/**
 * @brief Get the Arguments object
 * 
 * @param orig 
 * @param argue 
 * @param operation 
 * @return int 
 */
int getArguments(const char *orig, char ***argue, int *operation)
{
    int flag = 0;
    char *tmp;
    /* Reservamos memoria para copiar la candena ... pero la memoria justa */
    char *str = malloc(strlen(orig) + 1);
    strcpy(str, orig);
    char **args = NULL;
    char *restante = strchr(orig, 32);
    char *ret = NULL;

    /* Extraemos la primera palabra */
    tmp = strtok(str, " ");
    if (tmp == NULL)
    {
        return flag;
    }
    // printf("tmp: %s", tmp);
    if (0 == strcmp(tmp, "END"))
    {
        args = calloc(1, 5);
        args[0] = tmp;
        flag = 1;
        *argue = args;
        /* printf("%s %s", tmp, args[0]); */
        return flag;
    }
    else if (!strcmp(tmp, "INK"))
    {
        args = calloc(1, 5);
        args[0] = tmp;
        flag = 1;
        *argue = args;
        /* printf("%s %s", tmp, args[0]); */
        return flag;
    }
    else if (NULL == strstr(COMAND_STRING, tmp)) // La cadena a comparar debe ser la cadena de comandos
    {
        args = calloc(1, 5);
        args[0] = tmp;
        flag = 1;
        *argue = args;
        /* printf("%s %s", tmp, args[0]); */
        return flag;
    }
    else
    {

        ret = getCopyString(restante, 0, sizeof(restante));
    } // printf("retenida :%s%d\t%s", tmp,strcmp(tmp,"MOV"),orig);

    if (0 == strcmp(tmp, "MOV"))
    {

        args = (char **)calloc(3, 4);

        args[0] = tmp;
        char **argv = (char **)calloc(MAX_ARGS, MAX_CADENA);
        flag = getArgumentsFrom(ret, ",", argv);
        args[1] = argv[0];
        flag++;
        args[2] = argv[1];

        *operation = -1;
    }
    else if (0 == strcmp(tmp, "ADD"))
    {

        args = (char **)calloc(3, 4);

        args[0] = tmp;
        char **argv = (char **)calloc(MAX_ARGS, MAX_CADENA);

        flag = getArgumentsFrom(ret, ",", argv);
        flag++;
        args[1] = argv[0];
        args[2] = argv[1];

        *operation = -2;
    }
    else if (0 == strcmp(tmp, "SUB"))
    {

        args = (char **)calloc(3, 4);

        args[0] = tmp;
        char **argv = (char **)calloc(MAX_ARGS, MAX_CADENA);

        flag = getArgumentsFrom(ret, ",", argv);
        flag++;
        args[1] = argv[0];
        args[2] = argv[1];

        *operation = -3;
    }
    else if (0 == strcmp(tmp, "MUL"))
    {

        args = (char **)calloc(3, 4);

        args[0] = tmp;
        char **argv = (char **)calloc(MAX_ARGS, MAX_CADENA);

        flag = getArgumentsFrom(ret, ",", argv);
        flag++;
        args[1] = argv[0];
        args[2] = argv[1];

        *operation = -4;
    }
    else if (0 == strcmp(tmp, "DIV"))
    {

        args = (char **)calloc(3, 4);

        args[0] = tmp;
        char **argv = (char **)calloc(MAX_ARGS, MAX_CADENA);

        flag = getArgumentsFrom(ret, ",", argv);
        flag++;
        args[1] = argv[0];
        args[2] = argv[1];

        *operation = -5;
    }
    else if (0 == strcmp(tmp, "INC"))
    {
        args = calloc(2, 4);
        args[0] = tmp;
        char **argv = malloc(1 * MAX_CADENA);
        int argu = getArgumentsFrom(ret, ",", argv);
        if (1 < argu)
        {
            //printf("Error en los ARG\t\t\t\t<sdas");
            flag = -1;
        }
        else
        {

            flag = 2;
        }
        args[1] = argv[0];
    }
    else if (0 == strcmp(tmp, "DEC"))
    {
        args = calloc(2, 4);
        args[0] = tmp;
        char **argv = malloc(1 * MAX_CADENA);
        int argu = getArgumentsFrom(ret, ",", argv);
        if (1 < argu)
        {
            //printf("Error en los ARG\t\t\t\t<sdas");
            flag = -1;
        }
        else
        {
            flag = 2;
        }
        args[1] = argv[0];
    }

    else
    {
        args = calloc(1, 5);
        args[0] = tmp;
        flag = 1;
        *argue = args;
        /* printf("%s %s", tmp, args[0]); */
        printf("Argumentos Invalidos %s", tmp);
        return 0;
    }
    *argue = args;
    return flag;
}
NUM whoToken(char *argv)
{
    if (strcmp(argv, "AX"))
        return 1;
    else if (strcmp(argv, "AX"))
        return 2;
    else if (strcmp(argv, "BX"))
        return 3;
    else if (strcmp(argv, "CX"))
        return 4;
    else if (strcmp(argv, "DX"))
        return 5;
    else if (strcmp(argv, "TMP"))
        return 6;
    else
    {
        return 0;
    }
}

/**
 * @brief Asigna "A" a "B".
 *
 * @param A Parametro a asignar
 * @param B Valor a asignar
 * @return int
 */
int MOV(int A, int B)
{
    A = B;
    return A;
}
/**
 * @brief Añade a "A" el valor de "B"
 *
 * @param A
 * @param B
 * @return int
 */

int ADD(int A, int B)
{
    A += B;
    return A;
}
/*------------------------------------------*/
/***********************************\
Funcion SUB:
\***********************************/

int SUB(int a, int b)
{
    a -= b;
    return a;
}
/*------------------------------------------*/
/***********************************\
Funcion MUL:
\***********************************/
int MUL(int a, int b)
{
    a *= b;
    return a;
}
/*------------------------------------------*/
/***********************************\
Funcion OPER: (division)
    Divide
\***********************************/
int DIV(int a, int b)
{
    a = a / b;
    return a;
}
/**
 * @brief Incremento en 1 al valor
 * @param a
 * @return int
 */
int INC(int a)
{
    a++;
    return a;
}
/**
 * @brief Decremento en 1 al valor
 * @param a
 * @return int
 */
int DEC(int a)
{
    a--;
    return a;
}
