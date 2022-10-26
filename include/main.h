#ifndef __MAIN_H__
#define __MAIN_H__

#include <thread>

// internal files
#include "const.h"
#include "commands.h"
#include "drawing.h"
#include "fetch.h"
#include "decode.h"

// functions in main
void initializeFontInMemory(uint8_t memory[MEMORY_SIZE], uint8_t fontData[FONT_DATA_SIZE]);
void initializeMemory(uint8_t memory[MEMORY_SIZE]);
void delayTimerCycle(uint8_t* timer, bool* onSwitch);
void soundTimerCycle(uint8_t* timer, bool* onSwitch);

#endif