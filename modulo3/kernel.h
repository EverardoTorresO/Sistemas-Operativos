#include "interfaz.h"
#include "interprete.h"
#include "operaciones.h"
#include "default.h"
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include "cola.h"
/**
 * @brief Planificador de Corto Plazo
 * 
 * @param ptrReady Apuntador a la lista de Listos
 * @param ptrRunning Apuntador a la lista de Ejecutados
 * @param ptrExit Apuntador a la lista de Terminados
 */
void schedulingShortTerm(PCB **ptrReady, PCB **ptrRunning, PCB **ptrExit);
/**
 * @brief Ejecuta el IR del PCB que es ptrNow
 * 
 * @param ptrNow PCB que debe de ejecutar
 * @return int Retorna las banderas recibidas por executeLine(ptrNow);
 */
int executeIR(PCB *ptrNow);
/**
 * @brief Carga Contexto
 * 
 */
void loadContext();
/**
 * @brief Guarda Contexto
 * 
 */
void saveContext();
/**
 * @brief Obtiene un PCB para ser ejecutado
 * 
 * @param ptrReady_1 De donde extraemos el PCB
 * @return PCB* Retorna el PCB extraido
 */
PCB *getRunning(PCB **ptrReady_1);
/**
 * @brief 
 * 
 * @param toRunning 
 */
int executePCBRunning(PCB **toRunning);
