#ifndef BUS_H
#define BUS_H

#include "../cpu/cpu.h"
#include <stdint.h>


uint8_t bus_read(uint16_t addr);
void bus_write(uint16_t addr, uint8_t value);

void bus_reset();

#endif