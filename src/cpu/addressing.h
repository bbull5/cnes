#ifndef ADDRESSING_H
#define ADDRESSING_H

#include "cpu.h"
#include <stdint.h>


typedef enum {
    ADDR_ACCUMULATOR,
    ADDR_IMMEDIATE,
    ADDR_ZEROPAGE,
    ADDR_ZEROPAGE_X,
    ADDR_ZEROPAGE_Y,
    ADDR_ABSOLUTE,
    ADDR_ABSOLUTE_X,
    ADDR_ABSOLUTE_Y,
    ADDR_INDIRECT,
    ADDR_INDIRECT_X,
    ADDR_INDIRECT_Y,
    ADDR_RELATIVE,
    ADDR_IMPLIED
} AddressingMode;

typedef struct {
    uint16_t    base;
    uint16_t    effective;
} AddressResolution;


uint16_t resolve_address(CPU *cpu, AddressingMode mode);
AddressResolution resolve_address_with_base(CPU *cpu, AddressingMode mode);
uint8_t fetch_operand(CPU *cpu, AddressingMode mode);

#endif