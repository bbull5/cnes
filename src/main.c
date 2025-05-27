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
    // Setup
    CPU cpu;
    bus_reset();

    // Here, we assume that the reset vector is at 0xFFFC-0xFFFD and points
    // to the program at 0x8000
    bus_write(0xFFFC, 0x00);    // low byte
    bus_write(0xFFFD, 0x80);    // high byte

    cpu_reset(&cpu);
    init_instruction_table();

    // Test program
    uint8_t test_program[] = {
        0x69, 0x05
    };

    load_test_program(test_program, sizeof(test_program), 0x8000);

    // Initial state
    cpu.A = 10;
    cpu.P = 0x00;   // Clear all flags

    printf("Before:\n");
    cpu_print_state(&cpu);

    // Execute one instruction
    cpu_step(&cpu);

    printf("\nAfter:\n");
    cpu_print_state(&cpu);

    return 0;
}