// COMPILE WITH THIS COMMAND:
// gcc -std=c99 -Wall -DTEST_MODE -Isrc src/main.c src/cpu/*.c src/bus/*.c -o nes_test


#include <stdio.h>
#include <stdint.h>
#include "cpu/cpu.h"
#include "cpu/opcodes.h"
#include "bus/bus.h"


void load_test_program(const uint8_t *program, size_t size, uint16_t load_addr) {
    for (size_t i = 0; i < size; i++) {
        bus_write(load_addr + i, program[i]);
    }
}


int main(void) {
    // CPU setup
    CPU cpu;
    bus_reset();

    // Configure reset vector
    bus_write(0xFFFC, 0x00);    // low byte
    bus_write(0xFFFD, 0x80);    // high byte

    cpu_reset(&cpu);
    init_instruction_table();

    // Test program
    uint8_t test_program[] = {
        0xA9, 0x10,     // LDA #$10
        0x0A,           // ASL A
        0x00            // BRK
    };

    load_test_program(test_program, sizeof(test_program), 0x8000);

    cpu.P = 0x00;
    cpu.A = 0;

    printf("Initial State:\n");
    cpu_print_state(&cpu);
    printf("\n");

    // Run until BRK
    int n = 1;
    while (1) {
        uint8_t opcode = bus_read(cpu.PC);
        if (opcode == 0x00) break;
        cpu_step(&cpu);

        printf("Step %d:\n", n);
        cpu_print_state(&cpu);
        printf("\n");
        n++;
    }

    printf("Final State:\n");
    cpu_print_state(&cpu);
    printf("\n");


    return 0;
}