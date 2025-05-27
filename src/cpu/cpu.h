#ifndef CPU_H
#define CPU_H

#include <stdint.h>


// Status flag bit masks
#define FLAG_CARRY      0x01
#define FLAG_ZERO       0x02
#define FLAG_INTERRUPT  0X04
#define FLAG_DECIMAL    0x08
#define FLAG_BREAK      0x10
#define FLAG_UNUSED     0x20
#define FLAG_OVERFLOW   0x40
#define FLAG_NEGATIVE   0x80


typedef struct {
    // Registers
    uint16_t    PC;     // Program counter
    uint16_t    SP;     // Stack pointer
    uint16_t    A;      // Accumulator
    uint16_t    X;      // Index register X
    uint16_t    Y;      // Index register Y
    uint16_t    P;      // Status register

    // CPU cycles
    uint64_t cycles;
} CPU;


void cpu_reset(CPU *cpu);
void cpu_print_state(const CPU *cpu);
void cpu_step(CPU *cpu);

#endif