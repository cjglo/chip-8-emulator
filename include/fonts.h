#ifndef __FONTS_H__
#define __FONTS_H__

#include <stdint.h>

// Font Data
#define FONT_DATA_START 0x50
#define FONT_DATA_SIZE 80
// Font data, each row are sprite data for 0-F
#define FONT_DATA \
{             \
    0xF0, 0x90, 0x90, 0x90, 0xF0,  \
    0x20, 0x60, 0x20, 0x20, 0x70,  \
    0xF0, 0x10, 0xF0, 0x80, 0xF0,  \
    0xF0, 0x10, 0xF0, 0x10, 0xF0,  \
    0x90, 0x90, 0xF0, 0x10, 0x10,  \
    0xF0, 0x80, 0xF0, 0x10, 0xF0,  \
    0xF0, 0x80, 0xF0, 0x90, 0xF0,  \
    0xF0, 0x10, 0x20, 0x40, 0x40,  \
    0xF0, 0x90, 0xF0, 0x90, 0xF0,  \
    0xF0, 0x90, 0xF0, 0x10, 0xF0,  \
    0xF0, 0x90, 0xF0, 0x90, 0x90,  \
    0xE0, 0x90, 0xE0, 0x90, 0xE0,  \
    0xF0, 0x80, 0x80, 0x80, 0xF0,  \
    0xE0, 0x90, 0x90, 0x90, 0xE0,  \
    0xF0, 0x80, 0xF0, 0x80, 0xF0,  \
    0xF0, 0x80, 0xF0, 0x80, 0x80   \
};

#endif