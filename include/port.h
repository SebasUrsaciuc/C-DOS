#pragma once

#include "def.h"

/* Input byte through port. */
uint8 port_inb(uint16 port);

/* Output byte through port. */
void port_outb(uint16 port, uint8 data);

/* Input word through port. */
uint16 port_inw(uint16 port);

/* Output word through port. */
void port_outw(uint16 port, uint16 data);