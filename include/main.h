#ifndef __MAIN_H__
#define __MAIN_H__

// emulator constants
#define DISPLAY_HEIGHT 32
#define DISPLAY_WIDTH 64
#define MEMORY_SIZE 4096
#define STACK_SIZE 16
#define STARTING_REGISTER 0x200
#define CLOCK_EXECUTION_DELAY .0014 // CHIP-8 executes roughly 700 instructions/second

// libaries
#include <stdint.h>
#include <iostream>
#include <unistd.h>

// internal files
#include "commands.h"
#include "drawing.h"
#include "fetch.h"

// emulator types
struct uint12_struct
{
    u_int16_t bits : 12;
};

#endif
