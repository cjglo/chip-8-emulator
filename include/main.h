#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdint.h>
#include <iostream>

#include "commands.h"
#include "drawing.h"

// emulator constants
#define DISPLAY_HEIGHT 32
#define DISPLAY_WIDTH 64
#define MEMORY_SIZE 4096
#define STACK_SIZE 16

// emulator types
struct uint10_struct {
    u_int16_t bits : 12;
};

#endif