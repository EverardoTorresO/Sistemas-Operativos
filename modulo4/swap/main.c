#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IR_LEN 16 //ancho de la página
#define PAGE_SIZE 4 //alto de la página
#define SWAP_SIZE 10 //numero de marcos
//PARA LEER EL ARCHIVO BIANRIO DESDE LA TERMINAL: hexdump -v -e '"%010_ad  |" 16/1 "%_p" "|\n"' file.dat
void makeFile(int const ir_len, int const page_size, int const swap_size)
{
    int FRAME_SIZE = ir_len*page_size;

    FILE *file;
    file=fopen("file.dat","wb");
    if (file==NULL)
       {
           perror("fopen");
            exit(1);

        }

    char buffer[FRAME_SIZE*swap_size];
    memset(buffer,'A',FRAME_SIZE*swap_size*sizeof(char));
    fwrite(buffer, swap_size, FRAME_SIZE, file);

    

    fclose(file);
}

int main() {

    makeFile(IR_LEN,PAGE_SIZE,SWAP_SIZE);

    return 0;
}
