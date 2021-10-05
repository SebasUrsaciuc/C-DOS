#include "ps2.h"

#include "port.h"

void reset() {
    outb(PS2CTRL_COMPORT, PS2CTRL_COM_RESET);
}