#include "cpu.h"
#include "../bus/bus.h"
#include "opcodes.h"
#include "addressing.h"
#include <stdio.h>


void cpu_reset(CPU *cpu) {
    uint8_t low = bus_read(0xFFFC);
    uint8_t high = bus_read(0xFFFD);
    cpu->PC     = (high << 8) | low;    // Address of reset vector
    cpu->SP     = 0xFD;                 // Standard reset value
    cpu->A      = 0;
    cpu->X      = 0;
    cpu->Y      = 0;
    cpu->P      = 0x24;                 // IRQ disabled (unused flag set)
    cpu->cycles = 0;

    printf("[CPU] Reset vector = $%02X%02X\n", high, low);
}

void cpu_print_state(const CPU *cpu) {
    printf("CPU STATE:\n");
    printf("PC: $%04X  SP: $%02X\n", cpu->PC, cpu->SP);
    printf("A: $%02X  X: $%02X  Y: $%02X\n", cpu->A, cpu->X, cpu->Y);
    printf("P: %c%c%c%c%c%c%c%c\n",
           (cpu->P & FLAG_NEGATIVE) ? 'N' : '.',
           (cpu->P & FLAG_OVERFLOW) ? 'V' : '.',
           (cpu->P & FLAG_UNUSED) ? 'U' : '.',
           (cpu->P & FLAG_BREAK) ? 'B' : '.',
           (cpu->P & FLAG_DECIMAL) ? 'D' : '.',
           (cpu->P & FLAG_INTERRUPT) ? 'I' : '.',
           (cpu->P & FLAG_ZERO) ? 'Z' : '.',
           (cpu->P & FLAG_CARRY) ? 'C' : '.');
}

// void cpu_step(CPU *cpu) {
//     uint8_t opcode = bus_read(cpu->PC++);
//     Opcode inst = instruction_table[opcode];

//     // Execute instruction
//     inst.execute(cpu, inst.mode);
//     cpu->cycles += inst.cycles;
// }

void cpu_step(CPU *cpu) {
    uint8_t opcode = bus_read(cpu->PC++);
    Opcode inst = instruction_table[opcode];
    uint16_t base = 0, effective = 0;

    if (inst.add_cycle_on_page_cross) {
        // Peek ahead without mutating actual PC
        uint16_t saved_pc = cpu->PC;

        AddressResolution ar = resolve_address_with_base(cpu, inst.mode);
        base = ar.base;
        effective = ar.effective;

        cpu->PC = saved_pc;
    }

    inst.execute(cpu, inst.mode);
    cpu->cycles += inst.cycles;

    // Page cross penalty
    if (inst.add_cycle_on_page_cross && ((base & 0xFF00) != (effective & 0xFF00))) {
        cpu->cycles++;
    }
}