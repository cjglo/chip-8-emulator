#include "../../include/decode.h"

auto decode(uint16_t instruction) -> std::unique_ptr<Command> {

    std::unique_ptr<Command> command;

    switch(instruction) {
        // instruction decoding
        case 0x00E0:
            command = std::make_unique<ClearScreenCommand>();
            break;
        case 0x1000 ... 0x1FFF: 
        {
            uint12_struct address;
            address.bits = instruction; // only 3 least significant bytes saved, last byte is removed
            command = std::make_unique<JumpCommand>(address);
            break;
        }
        case 0x6000 ... 0x6FFF:
        {
            uint8_t  selected_register = (instruction & 0x0F00) >> 8; // first 4 bits after the 6
            uint8_t  value = instruction; // last 8 bits (since rest will be cut off)
            command = std::make_unique<SetRegister>(selected_register, value);
            break;
        }
        case 0x7000 ... 0x7FFF:
        {
            uint8_t  selected_register = (instruction & 0x0F00) >> 8; // first 4 bits after the 7
            uint8_t  value = instruction; // last 8 bits (since rest will be cut off)
            command = std::make_unique<AddValueToRegister>(selected_register, value);
            break;
        }
        case 0xA000 ... 0xAFFF:
        {
           uint12_struct i_register_address;
           i_register_address.bits = instruction; 
           command = std::make_unique<SetIndexRegister>(i_register_address);
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