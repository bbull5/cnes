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
    // AddressResolution ar = resolve_address_with_base(cpu, mode);
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
}

void and(CPU *cpu, AddressingMode mode) {
    // AddressResolution ar = resolve_address_with_base(cpu, mode);
    uint8_t operand = fetch_operand(cpu, mode);

    cpu->A &= operand;
    set_zn_flags(cpu, cpu->A);
}

void asl(CPU *cpu, AddressingMode mode) {
    if (mode == ADDR_ACCUMULATOR) {
        uint8_t value = cpu->A;

        if (value & 0x80) {
            cpu->P |= FLAG_CARRY;
        }
        else {
            cpu->P &= ~FLAG_CARRY;
        }

        value <<= 1;
        cpu->A = value;

        set_zn_flags(cpu, value);
    }
    else {
        uint16_t addr = resolve_address(cpu, mode);
        uint8_t value = bus_read(addr);

        if (value & 0x80) {
            cpu->P |= FLAG_CARRY;
        }
        else {
            cpu->P &= ~FLAG_CARRY;
        }

        value <<= 1;

        bus_write(addr, value);
        set_zn_flags(cpu, value);
    }
}

void bcc(CPU *cpu, AddressingMode mode) {
    return;
}

void bcs(CPU *cpu, AddressingMode mode) {
    return;
}

void beq(CPU *cpu, AddressingMode mode) {
    return;
}

void bit(CPU *cpu, AddressingMode mode) {
    return;
}

void bmi(CPU *cpu, AddressingMode mode) {
    return;
}

void bpl(CPU *cpu, AddressingMode mode) {
    return;
}

void brk(CPU *cpu, AddressingMode mode) {
    return;
}

void bvc(CPU *cpu, AddressingMode mode) {
    return;
}

void bvs(CPU *cpu, AddressingMode mode) {
    return;
}

void clc(CPU *cpu, AddressingMode mode) {
    return;
}

void cld(CPU *cpu, AddressingMode mode) {
    return;
}

void cli(CPU *cpu, AddressingMode mode) {
    return;
}

void clv(CPU *cpu, AddressingMode mode) {
    return;
}

void cmp(CPU *cpu, AddressingMode mode) {
    return;
}

void cpx(CPU *cpu, AddressingMode mode) {
    return;
}

void cpy(CPU *cpu, AddressingMode mode) {
    return;
}

void dec(CPU *cpu, AddressingMode mode) {
    return;
}

void dex(CPU *cpu, AddressingMode mode) {
    return;
}

void dey(CPU *cpu, AddressingMode mode) {
    return;
}

void eor(CPU *cpu, AddressingMode mode) {
    return;
}

void inc(CPU *cpu, AddressingMode mode) {
    return;
}

void inx(CPU *cpu, AddressingMode mode) {
    return;
}

void iny(CPU *cpu, AddressingMode mode) {
    return;
}

void jmp(CPU *cpu, AddressingMode mode) {
    return;
}

void jsr(CPU *cpu, AddressingMode mode) {
    return;
}

void lda(CPU *cpu, AddressingMode mode) {
    uint8_t operand = fetch_operand(cpu, mode);
    cpu->A = operand;
    set_zn_flags(cpu, cpu->A);
}

void ldx(CPU *cpu, AddressingMode mode) {
    return;
}

void ldy(CPU *cpu, AddressingMode mode) {
    return;
}

void lsr(CPU *cpu, AddressingMode mode) {
    return;
}

void ora(CPU *cpu, AddressingMode mode) {
    return;
}

void pha(CPU *cpu, AddressingMode mode) {
    return;
}

void php(CPU *cpu, AddressingMode mode) {
    return;
}

void pla(CPU *cpu, AddressingMode mode) {
    return;
}

void plp(CPU *cpu, AddressingMode mode) {
    return;
}

void rol(CPU *cpu, AddressingMode mode) {
    return;
}

void ror(CPU *cpu, AddressingMode mode) {
    return;
}

void rti(CPU *cpu, AddressingMode mode) {
    return;
}

void rts(CPU *cpu, AddressingMode mode) {
    return;
}

void sbc(CPU *cpu, AddressingMode mode) {
    return;
}

void sec(CPU *cpu, AddressingMode mode) {
    return;
}

void sed(CPU *cpu, AddressingMode mode) {
    return;
}

void sei(CPU *cpu, AddressingMode mode) {
    return;
}

void sta(CPU *cpu, AddressingMode mode) {
    return;
}

void stx(CPU *cpu, AddressingMode mode) {
    return;
}

void sty(CPU *cpu, AddressingMode mode) {
    return;
}

void tax(CPU *cpu, AddressingMode mode) {
    return;
}

void tay(CPU *cpu, AddressingMode mode) {
    return;
}

void tsx(CPU *cpu, AddressingMode mode) {
    return;
}

void txa(CPU *cpu, AddressingMode mode) {
    return;
}

void txs(CPU *cpu, AddressingMode mode) {
    return;
}

void tya(CPU *cpu, AddressingMode mode) {
    return;
}
