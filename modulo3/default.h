#ifndef _DEFAULT_H_
#define _DEFAULT_H_
#define NUM int
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
#define MAXPRIORITY 5
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <termios.h>
/**
 * @brief Codigos de Operacion
 * 
 */
typedef enum OPERATION_CODE
{
    DIVIDE_BY_CERO = -50,
    EMPTY_IR = -51,
    BAD_REGISTER = -52,
    BAD_INSTRUCTION = -53,
    SUCCESS = -54,
    ERROR_ARGUMENTS = -55,
    INVALID_ARGUMENTS = -56,
    ERROR_CLOSE_FILE=-57
} OPERATION_CODE;
typedef enum STATUS_PCB
{
    END = -2,
    ERROR = -1,
    READY = 0,
    RUNNING = 1,
    WAITING = 2
} STATUS_PCB;
typedef enum COMMAND_LINE
{
   QUIT=1,
   KILL=2,
   CREATE=3
} COMMAND_LINE;
int kbhit(void);
#endif