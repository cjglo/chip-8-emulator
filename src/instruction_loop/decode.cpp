#include "../../include/decode.h"

Command* decode(u_int16_t instruction) {

    Command* command;

    switch(instruction) {
        // instruction decoding
        case 0x00E0:
            command = new ClearScreenCommand();
            break;
        case 0x1000 ... 0x1FFF: 
            command = new JumpCommand(instruction);
    } 

    return command;
}