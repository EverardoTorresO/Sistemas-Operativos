#include "interfaz.h"
#include "interprete.h"
#include "operaciones.h"
#include "default.h"
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include "cola.h"

void schedulingShortTerm(PCB **ptrReady, PCB **ptrRunning, PCB **ptrExit);
void executeLine(PCB *ptrNow);
void loadContext();
void saveContext();
PCB *getRunning(PCB **ptrReady_1);
void executePCBRunning(PCB **toRunning);
void executeLine(PCB *ptrNow);