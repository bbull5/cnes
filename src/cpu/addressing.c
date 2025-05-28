#include <stdio.h>
#include "addressing.h"
#include "../bus/bus.h"


static uint8_t read_pc_byte (CPU *cpu) {
    return bus_read(cpu->PC++);
}

static uint16_t read_pc_word(CPU *cpu) {
    uint8_t low = read_pc_byte(cpu);
    uint8_t high = read_pc_byte(cpu);
    return (high << 8) | low;
}

uint16_t resolve_address(CPU *cpu, AddressingMode mode) {
    switch (mode) {
        case ADDR_IMMEDIATE:
            return cpu->PC++;
        
        case ADDR_ZEROPAGE:
            return read_pc_byte(cpu);
        
        case ADDR_ZEROPAGE_X:
            return (read_pc_byte(cpu) + cpu->X) & 0xFF;

        case ADDR_ZEROPAGE_Y:
            return (read_pc_byte(cpu) + cpu->Y) & 0xFF;

        case ADDR_ABSOLUTE:
            return read_pc_word(cpu);

        case ADDR_ABSOLUTE_X:
            return read_pc_word(cpu) + cpu->X;

        case ADDR_ABSOLUTE_Y:
            return read_pc_word(cpu) + cpu->Y;

        case ADDR_INDIRECT: {
            uint16_t addr = read_pc_word(cpu);
            uint8_t low = bus_read(addr);
            uint8_t high;

            // Emulate 6502 page boundary bug (very important to have this!!!)
            if ((addr & 0x00FF) == 0x00FF) {
                high = bus_read(addr & 0xFF00);
            }
            else {
                high = bus_read(addr + 1);
            }

            return (high << 8) | low;
        }

        case ADDR_INDIRECT_X: {
            uint8_t zp = (read_pc_byte(cpu) + cpu->X) & 0xFF;
            uint8_t low = bus_read(zp);
            uint8_t high = bus_read((zp + 1) & 0xFF);
            return (high << 8) | low;
        }

        case ADDR_INDIRECT_Y: {
            uint8_t zp = read_pc_byte(cpu);
            uint8_t low = bus_read(zp);
            uint8_t high = bus_read((zp + 1) & 0xFF);
            return ((high << 8) | low) + cpu->Y;
        }

        case ADDR_RELATIVE: {
            int8_t offset = (int8_t)read_pc_byte(cpu);
            return cpu->PC + offset;
        }

        case ADDR_IMPLIED:
        default:
            return 0;
    }
}

AddressResolution resolve_address_with_base(CPU *cpu, AddressingMode mode) {
    AddressResolution result = {0};

    switch (mode) {
        case ADDR_ABSOLUTE_X: {
            uint16_t base = read_pc_word(cpu);
            result.base = base;
            result.effective = base + cpu->X;
            break;
        }

        case ADDR_ABSOLUTE_Y: {
            uint16_t base = read_pc_word(cpu);
            result.base = base;
            result.effective = base + cpu->Y;
            break;
        }

        case ADDR_INDIRECT_Y: {
            uint8_t zp = read_pc_byte(cpu);
            uint8_t low = bus_read(zp);
            uint8_t high = bus_read((zp + 1) & 0xFF);
            uint16_t base = (high << 8) | low;
            result.base = base;
            result.effective = base + cpu->Y;
            break;
        }

        default:
            result.base = result.effective = resolve_address(cpu, mode);
    }

    return result;
}

uint8_t fetch_operand(CPU *cpu, AddressingMode mode) {
    switch (mode) {
        case ADDR_IMMEDIATE:
            return bus_read(cpu->PC++);

        case ADDR_ZEROPAGE:
            uint8_t addr = bus_read(cpu->PC++);
            return bus_read(addr);

        case ADDR_ZEROPAGE_X: {
            uint8_t base = bus_read(cpu->PC++);
            uint8_t addr = (base + cpu->X) & 0xFF;
            return bus_read(addr);
        }

        case ADDR_ZEROPAGE_Y: {
            uint8_t base = bus_read(cpu->PC++);
            uint8_t addr = (base +cpu->Y) & 0xFF;
            return bus_read(addr);
        }

        case ADDR_ABSOLUTE: {
            uint8_t low = bus_read(cpu->PC++);
            uint8_t high = bus_read(cpu->PC++);
            uint16_t addr = (high << 8) | low;
            return bus_read(addr);
        }

        case ADDR_ABSOLUTE_X: {
            uint8_t low = bus_read(cpu->PC++);
            uint8_t high = bus_read(cpu->PC++);
            uint16_t base = (high << 8) | low;
            uint16_t addr = base + cpu->X;
            return bus_read(addr);
        }

        case ADDR_ABSOLUTE_Y: {
            uint8_t low = bus_read(cpu->PC++);
            uint8_t high = bus_read(cpu->PC++);
            uint16_t base = (high << 8) | low;
            uint16_t addr = base + cpu->Y;
            return bus_read(addr);
        }

        case ADDR_INDIRECT_X: {
            uint8_t zp_addr = (bus_read(cpu->PC++) + cpu->X) & 0xFF;
            uint8_t low = bus_read(zp_addr);
            uint8_t high = bus_read((zp_addr + 1) & 0xFF);
            uint16_t addr = (high << 8) | low;
            return bus_read(addr);
        }

        case ADDR_INDIRECT_Y: {
            uint8_t zp = bus_read(cpu->PC++);
            uint8_t low = bus_read(zp);
            uint8_t high = bus_read((zp + 1) & 0xFF);
            uint16_t base = (high << 8) |  low;
            uint16_t addr = base + cpu->Y;
            return bus_read(addr);
        }

        case ADDR_ACCUMULATOR: {
            return cpu->A;
        }

        case ADDR_IMPLIED:
        case ADDR_RELATIVE:
        case ADDR_INDIRECT:

        default:
            fprintf(stderr, "[ERROR] fetch_operand called with unsupported mode: %d\n", mode);
            return 0;
    }
}