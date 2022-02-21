void tokenizerPrint(FILE *Archivo)
{   char *print;
    printf("IR:%s\t\tPC:%d,\tAX:%d,\tBX:%d,\tCX:%d,\tDX:%d\n", "    ", PC, AX, BX, CX, DX);
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
    mvprintw(3, 0, "IR:%s\t\tPC:%d,\tAX:%d,\tBX:%d,\tCX:%d,\tDX:%d\n", "    ", PC, AX, BX, CX, DX);
    tokenizerPrint(archivo);
    return 0;
}