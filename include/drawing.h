#ifndef __DRAWING_H__
#define __DRAWING_H__

// libraries
#include "raylib.h"

// internal files
#include "main.h"

// constants
#define WINDOW_HEIGHT 320
#define WINDOW_LENGTH 640

// func stubs
auto createWindow() -> void;
auto updateDisplay(bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH]) -> void;

#endif
