#ifndef __CONST_H__
#define __CONST_H__

// emulator constants
#define DISPLAY_HEIGHT 32
#define DISPLAY_WIDTH 64
#define MEMORY_SIZE 4096
#define SPRITE_WIDTH 8
#define STACK_SIZE 16
#define STARTING_REGISTER 0x200
#define VARIABLE_REGISTERS_SIZE 16
#define CLOCK_EXECUTION_DELAY .0014 // CHIP-8 executes roughly 700 instructions/second
#define TIMER_DELAY 0.016 // timers decrement 60 times per second
#define START_UP_DELAY 1 // so that human eye can catch screen before and after first drawing
#define DEFAULT_PROG_FILE_NAME "../ibmlogo.ch8"

// libaries
#include <stdint.h>
#include <iostream>
#include <unistd.h>

// emulator types
struct uint12_struct
{
    uint16_t bits : 12;
};

#endif