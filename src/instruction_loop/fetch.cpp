#include "../../include/fetch.h"

auto fetch(uint12_struct &pc, uint8_t memory[MEMORY_SIZE]) -> uint16_t {

    u_int16_t ps_address = pc.bits;

    u_int16_t instruction = memory[ps_address];
    instruction = instruction<<8;
    instruction += memory[ps_address+1];

    pc.bits += 2; // moves 2 spots every cycle, as 16 bits is full instruction

    return instruction;
}