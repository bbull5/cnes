#ifndef OPCODES_H
#define OPCODES_H

#include "cpu.h"
#include "addressing.h"
#include <stdint.h>


typedef void (*InstructionFn)(CPU *cpu, AddressingMode mode);

typedef struct {
    const char      *name;
    InstructionFn   execute;
    AddressingMode  mode;
    uint8_t         bytes;
    uint8_t         cycles;
    uint8_t         add_cycle_on_page_cross;
} Opcode;

extern Opcode instruction_table[256];

void init_instruction_table();


#endif