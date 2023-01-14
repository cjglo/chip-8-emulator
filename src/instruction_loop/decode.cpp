#include "../../include/decode.h"

auto decode(uint16_t instruction) -> std::unique_ptr<Command>
{

    std::unique_ptr<Command> command;

    switch (instruction)
    {
    // instruction decoding
    case 0x00E0:
        command = std::make_unique<ClearScreenCommand>();
        break;
    case 0x00EE:
        command = std::make_unique<PopSubRoutine>();
        break;
    case 0x1000 ... 0x1FFF:
    {
        uint12_struct address;
        address.bits = instruction; // only 3 least significant bytes saved, last byte is removed
        command = std::make_unique<JumpCommand>(address);
        break;
    }
    case 0x2000 ... 0x2FFF:
    {
        uint12_struct address;
        address.bits = instruction; // only 3 least significant bytes saved, last byte is removed
        command = std::make_unique<SubRoutines>(address);
        break;
    }
    case 0x3000 ... 0x3FFF: // Skip if X equal to Conditional
    {
        uint8_t register_x = (instruction & 0x0F00) >> 8;
        uint8_t condtional_val = instruction; // cuts off first 8 bits, leaving last 8
        command = std::make_unique<SkipXEqVar>(register_x, condtional_val);
        break;
    }
    case 0x4000 ... 0x4FFF:
    {
        uint8_t register_x = (instruction & 0x0F00) >> 8;
        uint8_t condtional_val = instruction; // cuts off first 8 bits, leaving last 8
        command = std::make_unique<SkipXNotEquVar>(register_x, condtional_val);
        break;
    }
    case 0x5000 ... 0x5FFF:
    {
        uint8_t register_x = (instruction & 0x0F00) >> 8;
        uint8_t register_y = (instruction & 0x00F0) >> 4;
        command = std::make_unique<SkipXEquY>(register_x, register_y);
        break;
    }
    case 0x6000 ... 0x6FFF:
    {
        uint8_t selected_register = (instruction & 0x0F00) >> 8; // first 4 bits after the 6
        uint8_t value = instruction;                             // last 8 bits (since rest will be cut off)
        command = std::make_unique<SetRegister>(selected_register, value);
        break;
    }
    case 0x7000 ... 0x7FFF:
    {
        uint8_t selected_register = (instruction & 0x0F00) >> 8; // first 4 bits after the 7
        uint8_t value = instruction;                             // last 8 bits (since rest will be cut off)
        command = std::make_unique<AddValueToRegister>(selected_register, value);
        break;
    }
    case 0x8000 ... 0x8FFF:
    {
        uint8_t x_register = instruction & 0x0F00;
        uint8_t y_register = instruction & 0x00F0;
        uint8_t operation = instruction & 0x000F;
        command = std::make_unique<LogicAndArithmetic>(x_register, y_register, operation);
        break;
    }
    case 0x9000 ... 0x9FFF:
    {
        uint8_t register_x = (instruction & 0x0F00) >> 8;
        uint8_t register_y = (instruction & 0x00F0) >> 4;
        command = std::make_unique<SkipXNotEquY>(register_x, register_y);
        break;
    }
    case 0xA000 ... 0xAFFF:
    {
        uint12_struct i_register_address;
        i_register_address.bits = instruction;
        command = std::make_unique<SetIndexRegister>(i_register_address);
        break;
    }
    case 0xB000 ... 0xBFFF:
    {
        uint12_struct address;
        address.bits = instruction; // 3 least significant bytes saved, last byte dropped
        command = std::make_unique<JumpWithOffset>(address);
        break;
    }
    case 0xC000 ... 0xCFFF:
    {
        uint8_t operand = instruction & 0xFF;
        uint8_t x_register = (instruction & 0x0F00) >> 8;
        command = std::make_unique<RandomNumber>(operand, x_register);
        break;
    }
    case 0xD000 ... 0xDFFF:
    {
        uint8_t x = (instruction & 0x0F00) >> 8; // first 4 bits after D is register to get x
        uint8_t y = (instruction & 0x00F0) >> 4; // next 4 bits is register to get y
        uint8_t height = (instruction & 0x000F); // last 4 bits is height
        command = std::make_unique<DisplayDraw>(x, y, height);
        break;
    }
    default:
        command = std::make_unique<InvalidCommand>(instruction);
    }

    return command;
}