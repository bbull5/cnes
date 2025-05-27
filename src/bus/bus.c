#include "bus.h"
#include <string.h>
#include <stdio.h>


static uint8_t ram[0x0800];     // 2 KB RAM (mirrored every 0x800 bytes)

#define ROM_SIZE 0x8000
static uint8_t rom[ROM_SIZE];


void bus_reset() {
    memset(ram, 0, sizeof(ram));
    memset(rom, 0, sizeof(rom));
}

uint8_t bus_read(uint16_t addr) {
    if (addr <= 0x1FFF) {
        return ram[addr % 0x0800];
    }
    else if (addr >= 0x8000 && addr <= 0xFFFF) {
        return rom[addr-0x8000];
    }
    else {
        printf("[BUS] Unhandled read at $%04X\n", addr);
        return 0;
    }
}

void bus_write(uint16_t addr, uint8_t value) {
    if (addr <= 0x1FFF) {
        // Internal RAM
        ram[addr % 0x0800] = value;
    }
    else if (addr >= 0x8000 && addr <= 0xFFFF) {
        #ifdef TEST_MODE
            rom[addr-0x8000] = value;
        #else
            printf("[BUS] Attempt to write to ROM at $%04X (ignored)\n", addr);
        #endif
    }
    else {
        // PPU, APU, IO, expansion
        printf("[BUS] Unhandled write at $%04X = $%02X\n", addr, value);
    }
}