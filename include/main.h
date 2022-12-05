#ifndef __MAIN_H__
#define __MAIN_H__

#include <thread>
#include <memory>
#include <fstream> 

// internal files
#include "const.h"
#include "commands.h"
#include "drawing.h"
#include "fetch.h"
#include "decode.h"
#include "fonts.h"

// functions in main
auto initializeFontInMemory(uint8_t memory[MEMORY_SIZE], uint8_t fontData[FONT_DATA_SIZE]) -> void;
auto initializeMemory(std::ifstream& programFile, uint8_t memory[MEMORY_SIZE]) -> void;
auto delayTimerCycle(uint8_t* timer, bool* onSwitch) -> void;
auto soundTimerCycle(uint8_t* timer, bool* onSwitch) -> void;

#endif