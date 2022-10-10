#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "const.h"
#include <stdint.h>

// testing and debugging
#define UNIMPLEMENTED_COMMAND_DEBUG_CALL std::cout<<"UNIMPLEMENTED COMMAND CALLED"<<std::endl;

// abstract Commmand Class
class Command {
    public:
        virtual void execute(uint8_t* memory, bool** display, uint16_t* stack, uint12_struct pc, uint16_t ir) = 0;
};

// all instruction classes
class ClearScreenCommand : public Command {
    public:
        void execute(uint8_t* memory, bool** display, uint16_t* stack, uint12_struct pc, uint16_t ir);
};

class JumpCommand : public Command {

    private:
        uint12_struct address;

    public:
        JumpCommand(uint16_t intruction);
        void execute(uint8_t* memory, bool** display, uint16_t* stack, uint12_struct pc, uint16_t ir);
};

#endif