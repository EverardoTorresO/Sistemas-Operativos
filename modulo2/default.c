/**
 * @file modulo1.c
 * @author José Everardo Torres Orozco & Octavio Corona Hernandez
 * @brief Es un mini interpete de instrucciones asm, acorde como vienen en los archivos instrucciones.asm error*.asm
 * @version 0.1
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "default.h"
#include "cola.h"

#include "interfaz.h"
#include "interprete.h"
#include "operaciones.h"
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include "kernel.h"

int kbhit(void)
{
    struct timeval tv;
    fd_set read_fd;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&read_fd);
    FD_SET(0, &read_fd);

    if (select(1, &read_fd, NULL, NULL, &tv) == -1)
        return 0;

    if (FD_ISSET(0, &read_fd))
        return 1;

    return 0;
}