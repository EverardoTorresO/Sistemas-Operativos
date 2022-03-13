#include "interfaz.h"

int main(){
    char *entrada;
    if(initInterface()==0)
        printf("An Error Ocurred");
    entrada=getTextFromTerminal();
    printw("%s",entrada);
    refresh();
    getch();
    removeInterface();

    return 0;
}