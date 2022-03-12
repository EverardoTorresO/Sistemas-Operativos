#ifndef _DEFAULT_H_
#define _DEFAULT_H_
#define NUM  int 
#define INT int
#define INSTRUCTION_LONG 3
#define CAD char
#define MAX_ARGS 10
#define MAX_CADENA 2
#define MAX_TERMINAL_STRING 100
#define COMAND_STRING "MOVADDSUBMULDIVINCDEC"
#define DELAY_TIMER 1
#define SECOND 1000000
#define MILISECOND 1000
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif  
enum ERORRS{__SEGMENT_FAULT=1,_COMMAND_ERROR,_INVALID_ARGUMENTS};
typedef enum STATUS_PCB{
    END=-2,
    ERROR=-1,
    READY=0,
    RUNNING=1
} STATUS_PCB;
#endif