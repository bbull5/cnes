/*
    Implementation details for Opcodes can be found at:
    https://www.nesdev.org/obelisk-6502-guide/reference.html#JMP
*/

#include "opcodes.h"
#include "instructions.h"


Opcode instruction_table[256];

void init_instruction_table(void) {
    // Add With Carry
    instruction_table[0x69] = (Opcode){"ADC", adc, ADDR_IMMEDIATE, 2, 2, 0};
    instruction_table[0x65] = (Opcode){"ADC", adc, ADDR_ZEROPAGE, 2, 3, 0};
    instruction_table[0x75] = (Opcode){"ADC", adc, ADDR_ZEROPAGE_X, 2, 4, 0};
    instruction_table[0x6D] = (Opcode){"ADC", adc, ADDR_ABSOLUTE, 3, 4, 0};
    instruction_table[0x7D] = (Opcode){"ADC", adc, ADDR_ABSOLUTE_X, 3, 4, 1};
    instruction_table[0x79] = (Opcode){"ADC", adc, ADDR_ABSOLUTE_Y, 3, 4, 1};
    instruction_table[0x61] = (Opcode){"ADC", adc, ADDR_INDIRECT_X, 2, 6, 0};
    instruction_table[0x71] = (Opcode){"ADC", adc, ADDR_INDIRECT_Y, 2, 5, 1};

    // Logical AND
    instruction_table[0x29] = (Opcode){"AND", and, ADDR_IMMEDIATE, 2, 2, 0};
    instruction_table[0x25] = (Opcode){"AND", and, ADDR_ZEROPAGE, 2, 3, 0};
    instruction_table[0x35] = (Opcode){"AND", and, ADDR_ZEROPAGE_X, 2, 4, 0};
    instruction_table[0x2D] = (Opcode){"AND", and, ADDR_ABSOLUTE, 3, 4, 0};
    instruction_table[0x3D] = (Opcode){"AND", and, ADDR_ABSOLUTE_X, 3, 4, 1};
    instruction_table[0x39] = (Opcode){"AND", and, ADDR_ABSOLUTE_Y, 3, 4, 1};
    instruction_table[0x21] = (Opcode){"AND", and, ADDR_INDIRECT_X, 2, 6, 0};
    instruction_table[0x31] = (Opcode){"AND", and, ADDR_INDIRECT_Y, 2, 5, 1};

    // Arithmetic Shift Left
    instruction_table[0x0A] = (Opcode){"ASL", asl, ADDR_ACCUMULATOR, 1, 2, 0};
    instruction_table[0x06] = (Opcode){"ASL", asl, ADDR_ZEROPAGE, 2, 5, 0};
    instruction_table[0x16] = (Opcode){"ASL", asl, ADDR_ZEROPAGE_X, 2, 6, 0};
    instruction_table[0x0E] = (Opcode){"ASL", asl, ADDR_ABSOLUTE, 3, 6, 0};
    instruction_table[0x1E] = (Opcode){"ASL", asl, ADDR_ABSOLUTE_X, 3, 7, 0};

    /*
        BRANCH INSTRUCTIONS HAVE CONDITIONAL VALUES FOR THE "ADD_CYCLE_ON_PAGE_CROSS" VALUE IN
        THE OPCODE STRUCT (see opcodes.h)
        THIS MEANS THAT WHEN YOU IMPLEMENT THE OPCODE IN instructions.c, YOU MUST ACCOUNT FOR THIS
        CONDITIONAL VALUE
        Basically, this just means add 1 cycle if branch taken and add 1 more cycle if a page
        is crossed
    */
    // Branch if Carry Clear
    instruction_table[0x90] = (Opcode){"BCC", bcc, ADDR_RELATIVE, 2, 2, 0};

    // Branch if Carry Set
    instruction_table[0xB0] = (Opcode){"BCS", bcs, ADDR_RELATIVE, 2, 2, 0};

    // Branch if Equal
    instruction_table[0xF0] = (Opcode){"BEQ", beq, ADDR_RELATIVE, 2, 2, 0};

    // Bit Test
    instruction_table[0x24] = (Opcode){"BIT", bit, ADDR_ZEROPAGE, 2, 3, 0};
    instruction_table[0x2c] = (Opcode){"BIT", bit, ADDR_ABSOLUTE, 3, 4, 0};

    // Branch if Minus
    instruction_table[0x30] = (Opcode){"BMI", bmi, ADDR_RELATIVE, 2, 2, 0};

    // Branch if Positive
    instruction_table[0xD0] = (Opcode){"BPL", bpl, ADDR_RELATIVE, 2, 2, 0};

    // Force Interrupt
    instruction_table[0x00] = (Opcode){"BRK", brk, ADDR_IMPLIED, 1, 7, 0};

    // Branch if Overflow Clear
    instruction_table[0x50] = (Opcode){"BVC", bvc, ADDR_RELATIVE, 2, 2, 0};

    // Branch if Overflow Set
    instruction_table[0x70] = (Opcode){"BVS", bvs, ADDR_RELATIVE, 2, 2, 0};

    // Clear Carry Flag
    instruction_table[0x18] = (Opcode){"CLC", clc, ADDR_IMPLIED, 1, 2, 0};

    // Clear Decimal Mode
    instruction_table[0xD8] = (Opcode){"CLD", cld, ADDR_IMPLIED, 1, 2, 0};

    // Clear Interrupt Disable
    instruction_table[0x58] = (Opcode){"CLI", cli, ADDR_IMPLIED, 1, 2, 0};

    // Clear Overflow Flag
    instruction_table[0xB8] = (Opcode){"CLV", clv, ADDR_IMPLIED, 1, 2, 0};

    // Compare
    instruction_table[0xC9] = (Opcode){"CMP", cmp, ADDR_IMMEDIATE, 2, 2, 0};
    instruction_table[0xC5] = (Opcode){"CMP", cmp, ADDR_ZEROPAGE, 2, 3, 0};
    instruction_table[0xD5] = (Opcode){"CMP", cmp, ADDR_ZEROPAGE_X, 2, 4, 0};
    instruction_table[0xCD] = (Opcode){"CMP", cmp, ADDR_ABSOLUTE, 3, 4, 0};
    instruction_table[0xDD] = (Opcode){"CMP", cmp, ADDR_ABSOLUTE_X, 3, 4, 1};
    instruction_table[0xD9] = (Opcode){"CMP", cmp, ADDR_ABSOLUTE_Y, 3, 4, 1};
    instruction_table[0xC1] = (Opcode){"CMP", cmp, ADDR_INDIRECT_X, 2, 6, 0};
    instruction_table[0xD1] = (Opcode){"CMP", cmp, ADDR_INDIRECT_Y, 2, 5, 1};

    // Compare X Register
    instruction_table[0xE0] = (Opcode){"CPX", cpx, ADDR_IMMEDIATE, 2, 2, 0};
    instruction_table[0xE4] = (Opcode){"CPX", cpx, ADDR_ZEROPAGE, 2, 3, 0};
    instruction_table[0xEC] = (Opcode){"CPX", cpx, ADDR_ABSOLUTE, 3, 4, 0};

    // Compare Y Register
    instruction_table[0xC0] = (Opcode){"CPY", cpy, ADDR_IMMEDIATE, 2, 2, 0};
    instruction_table[0xC4] = (Opcode){"CPY", cpy, ADDR_ZEROPAGE, 2, 3, 0};
    instruction_table[0xCC] = (Opcode){"CPY", cpy, ADDR_ABSOLUTE, 3, 4, 0};

    // Decrement Memory
    instruction_table[0xC6] = (Opcode){"DEC", dec, ADDR_ZEROPAGE, 2, 5, 0};
    instruction_table[0xD6] = (Opcode){"DEC", dec, ADDR_ZEROPAGE_X, 2, 6, 0};
    instruction_table[0xCE] = (Opcode){"DEC", dec, ADDR_ABSOLUTE, 3, 6, 0};
    instruction_table[0xDE] = (Opcode){"DEC", dec, ADDR_ABSOLUTE_X, 3, 7, 0};

    // Decrement X Register
    instruction_table[0xCA] = (Opcode){"DEX", dex, ADDR_IMPLIED, 1, 2, 0};

    // Decrement Y Register
    instruction_table[0x88] = (Opcode){"DEY", dey, ADDR_IMPLIED, 1, 2, 0};

    // Exclusive OR
    instruction_table[0x49] = (Opcode){"EOR", eor, ADDR_IMMEDIATE, 2, 3, 0};
    instruction_table[0x45] = (Opcode){"EOR", eor, ADDR_ZEROPAGE, 2, 3, 0};
    instruction_table[0x55] = (Opcode){"EOR", eor, ADDR_ZEROPAGE_X, 2, 4, 0};
    instruction_table[0x4D] = (Opcode){"EOR", eor, ADDR_ABSOLUTE, 3, 4, 0};
    instruction_table[0x5D] = (Opcode){"EOR", eor, ADDR_ABSOLUTE_X, 3, 4, 1};
    instruction_table[0x59] = (Opcode){"EOR", eor, ADDR_ABSOLUTE_Y, 3, 4, 1};
    instruction_table[0x41] = (Opcode){"EOR", eor, ADDR_INDIRECT_X, 2, 6, 0};
    instruction_table[0x51] = (Opcode){"EOR", eor, ADDR_INDIRECT_Y, 2, 5, 1};

    // Increment Memory
    instruction_table[0xE6] = (Opcode){"INC", inc, ADDR_ZEROPAGE, 2, 5, 0};
    instruction_table[0xF6] = (Opcode){"INC", inc, ADDR_ZEROPAGE_X, 2, 5, 0};
    instruction_table[0xEE] = (Opcode){"INC", inc, ADDR_ABSOLUTE, 3, 6, 0};
    instruction_table[0xFE] = (Opcode){"INC", inc, ADDR_ABSOLUTE_X, 3, 7, 0};

    // Increment X Register
    instruction_table[0xE8] = (Opcode){"INX", inx, ADDR_IMPLIED, 1, 2, 0};

    // Increment Y Register
    instruction_table[0xC8] = (Opcode){"INY", iny, ADDR_IMPLIED, 1, 2, 0};

    // Jump
    instruction_table[0x4C] = (Opcode){"JMP", jmp, ADDR_ABSOLUTE, 3, 3, 0};
    instruction_table[0x6C] = (Opcode){"JMP", jmp, ADDR_INDIRECT, 3, 5, 0};

    // Jump to Subroutine
    instruction_table[0x20] = (Opcode){"JSR", jsr, ADDR_ABSOLUTE, 3, 6, 0};

    // Load Accumulator
    instruction_table[0xA9] = (Opcode){"LDA", lda, ADDR_IMMEDIATE, 2, 2, 0};
    instruction_table[0xA5] = (Opcode){"LDA", lda, ADDR_ZEROPAGE, 2, 3, 0};
    instruction_table[0xB5] = (Opcode){"LDA", lda, ADDR_ZEROPAGE_X, 2, 4, 0};
    instruction_table[0xAD] = (Opcode){"LDA", lda, ADDR_ABSOLUTE, 3, 4, 0};
    instruction_table[0xBD] = (Opcode){"LDA", lda, ADDR_ABSOLUTE_X, 3, 4, 1};
    instruction_table[0xB9] = (Opcode){"LDA", lda, ADDR_ABSOLUTE_Y, 3, 4, 1};
    instruction_table[0xA1] = (Opcode){"LDA", lda, ADDR_INDIRECT_X, 2, 6, 0};
    instruction_table[0xB1] = (Opcode){"LDA", lda, ADDR_INDIRECT_Y, 2, 5, 1};

    // Load X Register
    instruction_table[0xA2] = (Opcode){"LDX", ldx, ADDR_IMMEDIATE, 2, 2, 0};
    instruction_table[0xA6] = (Opcode){"LDX", ldx, ADDR_ZEROPAGE, 2, 3, 0};
    instruction_table[0xB6] = (Opcode){"LDX", ldx, ADDR_ZEROPAGE_X, 2, 4, 0};
    instruction_table[0xAE] = (Opcode){"LDX", ldx, ADDR_ABSOLUTE, 3, 4, 0};
    instruction_table[0xBE] = (Opcode){"LDX", ldx, ADDR_ABSOLUTE_Y, 3, 4, 1};

    // Load Y Register
    instruction_table[0xA0] = (Opcode){"LDY", ldy, ADDR_IMMEDIATE, 2, 2, 0};
    instruction_table[0xA4] = (Opcode){"LDY", ldy, ADDR_ZEROPAGE, 2, 3, 0};
    instruction_table[0xB4] = (Opcode){"LDY", ldy, ADDR_ZEROPAGE_X, 2, 4, 0};
    instruction_table[0xAC] = (Opcode){"LDY", ldy, ADDR_ABSOLUTE, 3, 4, 0};
    instruction_table[0xBC] = (Opcode){"LDY", ldy, ADDR_ABSOLUTE_X, 3, 4, 1};

    // Logical Shift Right
    instruction_table[0x4A] = (Opcode){"LSR", lsr, ADDR_ACCUMULATOR, 1, 2, 0};
    instruction_table[0x46] = (Opcode){"LSR", lsr, ADDR_ZEROPAGE, 2, 4, 0};
    instruction_table[0x56] = (Opcode){"LSR", lsr, ADDR_ZEROPAGE_X, 2, 6, 0};
    instruction_table[0x4E] = (Opcode){"LSR", lsr, ADDR_ABSOLUTE, 3, 6, 0};
    instruction_table[0x5E] = (Opcode){"LSR", lsr, ADDR_ABSOLUTE_X, 3, 7, 0};

    // No Operation
    instruction_table[0xEA] = (Opcode){"LSR", lsr, ADDR_IMPLIED, 1, 2, 0};

    // Logical Inclusive OR
    instruction_table[0x09] = (Opcode){"ORA", ora, ADDR_IMMEDIATE, 2, 2, 0};
    instruction_table[0x05] = (Opcode){"ORA", ora, ADDR_ZEROPAGE, 2, 3, 0};
    instruction_table[0x15] = (Opcode){"ORA", ora, ADDR_ZEROPAGE_X, 2, 4, 0};
    instruction_table[0x0D] = (Opcode){"ORA", ora, ADDR_ABSOLUTE, 3, 4, 0};
    instruction_table[0x1D] = (Opcode){"ORA", ora, ADDR_ABSOLUTE_X, 3, 4, 1};
    instruction_table[0x19] = (Opcode){"ORA", ora, ADDR_ABSOLUTE_Y, 3, 4, 1};
    instruction_table[0x01] = (Opcode){"ORA", ora, ADDR_INDIRECT_X, 2, 6, 0};
    instruction_table[0x11] = (Opcode){"ORA", ora, ADDR_INDIRECT_Y, 2, 5, 1};

    // Push Accumulator
    instruction_table[0x48] = (Opcode){"PHA", pha, ADDR_IMPLIED, 1, 3, 0};

    // Push Processor Status
    instruction_table[0x08] = (Opcode){"PHP", php, ADDR_IMPLIED, 1, 3, 0};

    // Pull Accumulator
    instruction_table[0x68] = (Opcode){"PLA", pla, ADDR_IMPLIED, 1, 4, 0};

    // Pull Processor Status
    instruction_table[0x28] = (Opcode){"PLP", plp, ADDR_IMPLIED, 1, 4, 0};

    // Rotate Left
    instruction_table[0x2A] = (Opcode){"ROL", rol, ADDR_ACCUMULATOR, 1, 2, 0};
    instruction_table[0x26] = (Opcode){"ROL", rol, ADDR_ZEROPAGE, 2, 5, 0};
    instruction_table[0x36] = (Opcode){"ROL", rol, ADDR_ZEROPAGE_X, 2, 6, 0};
    instruction_table[0x2E] = (Opcode){"ROL", rol, ADDR_ABSOLUTE, 3, 6, 0};
    instruction_table[0x3E] = (Opcode){"ROL", rol, ADDR_ABSOLUTE_X, 3, 7, 0};

    // Rotate Right
    instruction_table[0x6A] = (Opcode){"ROR", ror, ADDR_ACCUMULATOR, 1, 2, 0};
    instruction_table[0x66] = (Opcode){"ROR", ror, ADDR_ZEROPAGE, 2, 5, 0};
    instruction_table[0x76]  = (Opcode){"ROR", ror, ADDR_ZEROPAGE_X, 2, 6, 0};
    instruction_table[0x6E] = (Opcode){"ROR", ror, ADDR_ABSOLUTE, 3, 6, 0};
    instruction_table[0x7E] = (Opcode){"ROR", ror, ADDR_ABSOLUTE_X, 3, 7, 0};

    // Return from Interrupt
    instruction_table[0x40] = (Opcode){"RTI", rti, ADDR_IMPLIED, 1, 6, 0};

    // Return from Subroutine
    instruction_table[0x60] = (Opcode){"RTS", rts, ADDR_IMPLIED, 1, 6, 0};

    // Subtract with Carry
    instruction_table[0xE9] = (Opcode){"SBC", sbc, ADDR_IMMEDIATE, 2, 2, 0};
    instruction_table[0xE5] = (Opcode){"SBC", sbc, ADDR_ZEROPAGE, 2, 3, 0};
    instruction_table[0xF5] = (Opcode){"SBC", sbc, ADDR_ZEROPAGE_X, 2, 4, 0};
    instruction_table[0xED] = (Opcode){"SBC", sbc, ADDR_ABSOLUTE, 3, 4, 0};
    instruction_table[0xFD] = (Opcode){"SBC", sbc, ADDR_ABSOLUTE_X, 3, 4, 1};
    instruction_table[0xF9] = (Opcode){"SBC", sbc, ADDR_ABSOLUTE_Y, 3, 4, 1};
    instruction_table[0xE1] = (Opcode){"SBC", sbc, ADDR_INDIRECT_X, 2, 6, 0};
    instruction_table[0xF1] = (Opcode){"SBC", sbc, ADDR_INDIRECT_Y, 2, 5, 1};

    // Set Carry Flag
    instruction_table[0x38] = (Opcode){"SEC", sec, ADDR_IMPLIED, 1, 2, 0};

    // Set Decimal Flag
    instruction_table[0xF8] = (Opcode){"SED", sed, ADDR_IMPLIED, 1, 2, 0};

    // Set Interrupt Disable
    instruction_table[0x78] = (Opcode){"SEI", sei, ADDR_IMPLIED, 1, 2, 0};

    // Store Accumulator
    instruction_table[0x85] = (Opcode){"STA", sta, ADDR_ZEROPAGE, 2, 3, 0};
    instruction_table[0x95] = (Opcode){"STA", sta, ADDR_ZEROPAGE_X, 2, 4, 0};
    instruction_table[0x8D] = (Opcode){"STA", sta, ADDR_ABSOLUTE, 3, 4, 0};
    instruction_table[0x9D] = (Opcode){"STA", sta, ADDR_ABSOLUTE_X, 3, 5, 0};
    instruction_table[0x99] = (Opcode){"STA", sta, ADDR_ABSOLUTE_Y, 3, 5, 0};
    instruction_table[0x81] = (Opcode){"STA", sta, ADDR_INDIRECT_X, 2, 6, 0};
    instruction_table[0x91] = (Opcode){"STA", sta, ADDR_INDIRECT_Y, 2, 6, 0};

    // Store X Register
    instruction_table[0x86] = (Opcode){"STX", stx, ADDR_ZEROPAGE, 2, 3, 0};
    instruction_table[0x96] = (Opcode){"STX", stx, ADDR_ZEROPAGE_Y, 2, 4, 0};
    instruction_table[0x8E] = (Opcode){"STX", stx, ADDR_ABSOLUTE, 3, 4, 0};

    // Store Y Register
    instruction_table[0x84] = (Opcode){"STY", sty, ADDR_ZEROPAGE, 2, 3, 0};
    instruction_table[0x94] = (Opcode){"STY", sty, ADDR_ZEROPAGE_X, 2, 4, 0};
    instruction_table[0x8C] = (Opcode){"STY", sty, ADDR_ABSOLUTE, 3, 4, 0};

    // Transfer Accumulator to X
    instruction_table[0xAA] = (Opcode){"TAX", tax, ADDR_IMPLIED, 1, 2, 0};

    // Transfer Accumulator to Y
    instruction_table[0xA8] = (Opcode){"TAY", tay, ADDR_IMPLIED, 1, 2, 0};

    // Transfer Stack Pointer to X
    instruction_table[0xBA] = (Opcode){"TSX", tsx, ADDR_IMPLIED, 1, 2, 0};

    // Transfer X to Accumulator
    instruction_table[0x8A] = (Opcode){"TXA", txa, ADDR_IMPLIED, 1, 2, 0};

    // Transfer X to Stack Pointer
    instruction_table[0x9A] = (Opcode){"TXS", txs, ADDR_IMPLIED, 1, 2, 0};

    // Transfer Y to Accumulator
    instruction_table[0x98] = (Opcode){"TYA", tya, ADDR_IMPLIED, 1, 2, 0};
}