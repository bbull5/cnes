#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "cpu.h"
#include "addressing.h"


void adc(CPU *cpu, AddressingMode mode);
void and(CPU *cpu, AddressingMode mode);
void asl(CPU *cpu, AddressingMode mode);
void bcc(CPU *cpu, AddressingMode mode);
void bcs(CPU *cpu, AddressingMode mode);
void beq(CPU *cpu, AddressingMode mode);
void bit(CPU *cpu, AddressingMode mode);
void bmi(CPU *cpu, AddressingMode mode);
void bne(CPU *cpu, AddressingMode mode);
void bpl(CPU *cpu, AddressingMode mode);
void brk(CPU *cpu, AddressingMode mode);
void bvc(CPU *cpu, AddressingMode mode);
void bvs(CPU *cpu, AddressingMode mode);
void clc(CPU *cpu, AddressingMode mode);
void cld(CPU *cpu, AddressingMode mode);
void cli(CPU *cpu, AddressingMode mode);
void clv(CPU *cpu, AddressingMode mode);
void cmp(CPU *cpu, AddressingMode mode);
void cpx(CPU *cpu, AddressingMode mode);
void cpy(CPU *cpu, AddressingMode mode);
void dec(CPU *cpu, AddressingMode mode);
void dex(CPU *cpu, AddressingMode mode);
void dey(CPU *cpu, AddressingMode mode);
void eor(CPU *cpu, AddressingMode mode);
void inc(CPU *cpu, AddressingMode mode);
void inx(CPU *cpu, AddressingMode mode);
void iny(CPU *cpu, AddressingMode mode);
void jmp(CPU *cpu, AddressingMode mode);
void jsr(CPU *cpu, AddressingMode mode);
void lda(CPU *cpu, AddressingMode mode);
void ldx(CPU *cpu, AddressingMode mode);
void ldy(CPU *cpu, AddressingMode mode);
void lsr(CPU *cpu, AddressingMode mode);
void nop(CPU *cpu, AddressingMode mode);
void ora(CPU *cpu, AddressingMode mode);
void pha(CPU *cpu, AddressingMode mode);
void php(CPU *cpu, AddressingMode mode);
void pla(CPU *cpu, AddressingMode mode);
void plp(CPU *cpu, AddressingMode mode);
void rol(CPU *cpu, AddressingMode mode);
void ror(CPU *cpu, AddressingMode mode);
void rti(CPU *cpu, AddressingMode mode);
void rts(CPU *cpu, AddressingMode mode);
void sbc(CPU *cpu, AddressingMode mode);
void sec(CPU *cpu, AddressingMode mode);
void sed(CPU *cpu, AddressingMode mode);
void sei(CPU *cpu, AddressingMode mode);
void sta(CPU *cpu, AddressingMode mode);
void stx(CPU *cpu, AddressingMode mode);
void sty(CPU *cpu, AddressingMode mode);
void tax(CPU *cpu, AddressingMode mode);
void tay(CPU *cpu, AddressingMode mode);
void tsx(CPU *cpu, AddressingMode mode);
void txa(CPU *cpu, AddressingMode mode);
void txs(CPU *cpu, AddressingMode mode);
void tya(CPU *cpu, AddressingMode mode);


#endif