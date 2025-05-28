#include "cpu.h"
#include "../bus/bus.h"
#include "instructions.h"
#include "addressing.h"
#include <stdint.h>


/*
    STATUS REGISTER HELPER FUNCTIONS
*/

static void set_zn_flags(CPU *cpu, uint8_t value) {
    if (value == 0) {
        cpu->P |= FLAG_ZERO;
    }
    else {
        cpu->P &= ~FLAG_ZERO;
    }

    if (value & 0x80) {
        cpu->P |= FLAG_NEGATIVE;
    }
    else {
        cpu->P &= ~FLAG_NEGATIVE;
    }
}



/*
    OPCODE IMPLEMENTATIONS
*/

void adc(CPU *cpu, AddressingMode mode) {
    AddressResolution ar = resolve_address_with_base(cpu, mode);
    uint8_t operand = fetch_operand(cpu, mode);
    uint16_t sum = cpu->A + operand + (cpu->P & FLAG_CARRY ? 1 : 0);

    // Set Carry Flag (set bit 8)
    if (sum > 0xFF) {
        cpu->P |= FLAG_CARRY;
    }
    else {
        cpu->P &= ~FLAG_CARRY;
    }

    // Set Overflow Flag
    if (~(cpu->A ^ operand) & (cpu->A ^ sum) & 0x80) {
        cpu->P |= FLAG_OVERFLOW;
    }
    else {
        cpu->P &= ~FLAG_OVERFLOW;
    }

    cpu->A = (uint8_t)sum;
    set_zn_flags(cpu, cpu->A);

    // Page cross penalty
    if ((ar.base & 0xFF00) != (ar.effective & 0xFF00) && (mode == ADDR_ABSOLUTE_X || mode == ADDR_ABSOLUTE_Y || mode == ADDR_INDIRECT_Y)) {
        cpu->cycles++;
    }
}
