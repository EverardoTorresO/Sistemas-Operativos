#ifndef _DEFAULT_H_
#define _DEFAULT_H_
#define NUM  int 
#define INT int
#define INSTRUCTION_LONG 3
#define CAD char
#define MAX_ARGS 4
#define MAX_CADENA 2
#define MAX_TERMINAL_STRING 100
#define COMAND_STRING "MOVADDSUBMULDIVINCDEC"
#define DELAY_TIMER 1000
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif  
enum errors{__SEGMENT_FAULT=1,_COMMAND_ERROR,_INVALID_ARGUMENTS};
typedef struct TOKEN{
    INT instruction;
    CAD register1;
    NUM valueRegister1;
        CAD register2;
    NUM valueRegister2;
    int pc;
    struct TOKEN*next;

}TOKEN;
#endif