#ifndef __MAIN_H__
#define __MAIN_H__

// internal files
#include "const.h"
#include "commands.h"
#include "drawing.h"
#include "fetch.h"
#include "decode.h"

// functions in main
void initializeFontInMemory(uint8_t memory[MEMORY_SIZE], uint8_t fontData[FONT_DATA_SIZE]);
void initializeMemory(uint8_t memory[MEMORY_SIZE]);

#endif