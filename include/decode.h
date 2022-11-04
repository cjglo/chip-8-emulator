#ifndef __DECODE_H__
#define __DECODE_H__

#include <memory>

#include "commands.h"

auto decode(uint16_t instruction) -> std::unique_ptr<Command>;

#endif