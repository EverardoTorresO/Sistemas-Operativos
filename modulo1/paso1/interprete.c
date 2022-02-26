#include "interprete.h"
#include "operaciones.h"

int tokenizer(FILE *Archivo)
{
    int FLAG_TOKEN = 0;
    char *print = malloc(100);

    sprintf(print, "IR:%s\t\tPC:%d,\tAX:%d,\tBX:%d,\tCX:%d,\tDX:%d\n", "    ", PC, AX, BX, CX, DX);
    printf("%s\n", print);
    char str[30];
    while (fgets(str, sizeof(str), Archivo) != NULL)
    {
        int len = strlen(str);
        // Verificamos si el último caracter es un salto de línea

        if (str[len - 1] == '\n')
            // Eliminamos el salto de línea
            str[len - 1] = '\0';

        FLAG_TOKEN = executeToken(&print, str);
        printf("%s\n", print);

        switch (FLAG_TOKEN)
        {
        case 0:
            printf("Linea Vacia: No Execute\n");
            return -1;
            break;
        case 1:
            printf("BAD REGISTER\n");
            return -1;
        case 2:
            printf("END\n");
            return -2;
        case 3:
            printf("Divide By Cero\n");
            return -2;
            break;
        case 4:
            printf("BAD INSTRUCTION\n");
            return -1;
            break;
        case 5:
            printf("Succes\n");
            break;
        }
    }
    return 0;
}
NUM executeToken(char **source, char *cad)
{
    char **args;
    int operation = 0;

    int argc = getArguments(cad, &args, &operation);
    if (argc == -1)
    {
        sprintf(*source, "IR:%s   \tPC:%d,\tAX:%d,\tBX:%d,\tCX:%d,\tDX:%d\n", cad, PC, AX, BX, CX, DX);
        return 1;
        
    }
    int flag = doOperation(args);
    if (flag && argc > 0)
    {
        if (flag == 5)
        {
            PC++;
        }

        sprintf(*source, "IR:%s   \tPC:%d,\tAX:%d,\tBX:%d,\tCX:%d,\tDX:%d\n", cad, PC, AX, BX, CX, DX);
        return flag;
    }
    else if (argc > 0)
    {
        PC++;
        sprintf(*source, "IR:%s   \tPC:%d,\tAX:%d,\tBX:%d,\tCX:%d,\tDX:%d\n", cad, PC, AX, BX, CX, DX);
        return flag;
    }   else if (argc == 0)
    {

        sprintf(*source, "IR:%s   \tPC:%d,\tAX:%d,\tBX:%d,\tCX:%d,\tDX:%d\n", cad, PC, AX, BX, CX, DX);
        return argc;
    }
    return flag;
}
/**
 * @def Funcion doOperation: Trabaja sobre 1 sola linea de codigo.
 * @param instrucciones es una linea de codigo asm
 * @brief retorna: 0 Linea vacia, 1 Registro invalido, 2 Fin del archivo, 3 Div by cero; 4 Instruccion no valida. 5 se Realizo la accion.
 */
int doOperation(char **instrucciones)
{
    int retorno = 0;

    if (strlen(instrucciones[0]) == 0 || strcmp("\0", instrucciones[0]) == 0||  strcmp("\n", instrucciones[0]) == 0 ||strcmp("", instrucciones[0]) == 0)
    {
        retorno = 0;
    }
    else
    {
        if (strcmp("MOV", instrucciones[0]) == 0)
        {
            strcpy(IR, "MOV");
            retorno = 5;
            switch (getRegister(instrucciones[1]))
            {
            case 1:
                AX = MOV(AX, getValue(instrucciones[2]));
                break;
            case 2:
                BX = MOV(BX, getValue(instrucciones[2]));
                break;
            case 3:
                CX = MOV(CX, getValue(instrucciones[2]));
                break;
            case 4:
                DX = MOV(DX, getValue(instrucciones[2]));
                break;
            case 0:
                retorno = 1;
                break;
            }
        }
        else if (strcmp("ADD", instrucciones[0]) == 0)
        {
            strcpy(IR, "ADD");
            retorno = 5;
            switch (getRegister(instrucciones[1]))
            {
            case 1:
                AX = ADD(AX, getValue(instrucciones[2]));
                break;
            case 2:
                BX = ADD(BX, getValue(instrucciones[2]));
                break; /*  */
            case 3:
                CX = ADD(CX, getValue(instrucciones[2]));
                break;
            case 4:
                DX = ADD(DX, getValue(instrucciones[2]));
                break;
            case 0:
                retorno = 1;
                break;
            }
        }
        else if (strcmp("SUB", instrucciones[0]) == 0)
        {
            strcpy(IR, "SUB");
            retorno = 5;
            switch (getRegister(instrucciones[1]))
            {
            case 1:
                AX = SUB(AX, getValue(instrucciones[2]));
                break;
            case 2:
                BX = SUB(BX, getValue(instrucciones[2]));
                break;
            case 3:
                CX = SUB(CX, getValue(instrucciones[2]));
                break;
            case 4:
                DX = SUB(DX, getValue(instrucciones[2]));
                break;
            case 0:
                retorno = 1;
                break;
            }
        }
        else if (strcmp("MUL", instrucciones[0]) == 0)
        {
            strcpy(IR, "MUL");
            retorno = 5;
            switch (getRegister(instrucciones[1]))
            {
            case 1:
                AX = MUL(AX, getValue(instrucciones[2]));
                break;
            case 2:
                BX = MUL(BX, getValue(instrucciones[2]));
                break;
            case 3:
                CX = MUL(CX, getValue(instrucciones[2]));
                break;
            case 4:
                DX = MUL(DX, getValue(instrucciones[2]));
                break;
            case 0:
                retorno = 1;
                break;
            }
        }
        else if (strcmp("DIV", instrucciones[0]) == 0)
        {
            strcpy(IR, "DIV");
            retorno = 5;
            if (getValue(instrucciones[2]) == 0)
            {
                retorno = 3;
            }
            else
            {
                switch (getRegister(instrucciones[1]))
                {
                case 1:
                    AX = DIV(AX, getValue(instrucciones[2]));
                    break;
                case 2:
                    BX = DIV(BX, getValue(instrucciones[2]));
                    break;
                case 3:
                    CX = DIV(CX, getValue(instrucciones[2]));
                    break;
                case 4:
                    DX = DIV(DX, getValue(instrucciones[2]));
                    break;
                case 0:
                    retorno = 1;
                    break;
                }
            }
        }
        else if (strcmp("INC", instrucciones[0]) == 0)
        {
            strcpy(IR, "INC");
            retorno = 5;
            switch (getRegister(instrucciones[1]))
            {
            case 1:
                AX++;
                break;
            case 2:
                BX++;
                break;
            case 3:
                CX++;
                break;
            case 4:
                DX++;
                break;
            case 0:
                retorno = 1;
                break;
            }
        }
        else if (strcmp("DEC", instrucciones[0]) == 0)
        {
            strcpy(IR, "DEC");
            retorno = 5;
            switch (getRegister(instrucciones[1]))
            {
            case 1:
                AX--;
                break;
            case 2:
                BX--;
                break;
            case 3:
                CX--;
                break;
            case 4:
                DX--;
                break;
            case 0:
                retorno = 1;
                break;
            }
        }
        else if (strcmp("END", instrucciones[0]) == 0)
        {
            retorno = 2;
        }
        else
        {
            retorno = 4;
        }
    } /*Fin de la instruccion*/
    return retorno;
}
/**
 * @brief Retorna el valor del registro si existe
 * @param registro Obtiene el registro dentro de la liena asm
 * @fn getRegister()
 */
int getRegister(char registro[10])
{
    if (strcmp(registro, " AX") == 0 || strcmp(registro, "AX") == 0)
    {
        return 1;
    }
    if (strcmp(registro, " BX") == 0 || strcmp(registro, "BX") == 0)
    {
        return 2;
    }
    if (strcmp(registro, " CX") == 0 || strcmp(registro, "CX") == 0)
    {
        return 3;
    }
    if (strcmp(registro, " DX") == 0 || strcmp(registro, "DX") == 0)
    {
        return 4;
    }
    else
    {
        return 0;
    }
}
/**
 * @brief Obttiene el valor del registro. El valor del registro si se obtiene es  el valor numerico o el de la sentencia
 * @param valor Ultimo argumento de la linea asm
 *
 */

int getValue(char valor[10])
{
    if (strcmp("AX", valor) == 0)
    {
        return AX;
    }
    if (strcmp("BX", valor) == 0)
    {
        return BX;
    }
    if (strcmp("CX", valor) == 0)
    {
        return CX;
    }
    if (strcmp("DX", valor) == 0)
    {
        return DX;
    }
    else
    {
        return atoi(valor);
    }
}

int whoOperation(char *cad)
{
    return 1;
}