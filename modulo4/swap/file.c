#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

//PARA LEER EL ARCHIVO BIANRIO DESDE LA TERMINAL: hexdump -v -e '"%010_ad  |" 16/1 "%_p" "|\n"' file.dat


void makeFile(int const IR_LEN, int const PAGE_SIZE, int const SWAP_SIZE)
{
    int FRAME_SIZE = IR_LEN*PAGE_SIZE;

    FILE *file;
    file=fopen("file.dat","wb");
    if (file==NULL)
       {
           perror("fopen");
            exit(1);

        }

    char buffer[FRAME_SIZE];
    memset(buffer,0,FRAME_SIZE*sizeof(char));
    int i;
    for(i=0;i<10;i++){
    fwrite(buffer, 1, FRAME_SIZE, file);

    }

    fclose(file);
}
