#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "const.h"
#include <stdint.h>

// testing and debugging
#define UNIMPLEMENTED_COMMAND_DEBUG_CALL std::cout<<"UNIMPLEMENTED COMMAND CALLED"<<std::endl;

// abstract Commmand Class
class Command {
    public:
        // TODO: May want to change execute having every param. Could make this enum and make methods in execute
        // stage but that would seperate Command from its method and not sure I like that either
        virtual auto execute(
            uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], 
            uint16_t* stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE], 
            uint12_struct pc, uint16_t ir
        ) -> void = 0;
};

// all instruction classes
class ClearScreenCommand : public Command {
    public:
        auto execute(
            uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], 
            uint16_t* stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
            uint12_struct pc, uint16_t ir
        ) -> void;
};

class JumpCommand : public Command {

    private:
        uint12_struct address;

    public:
        JumpCommand(uint12_struct address);
        auto execute(
            uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], 
            uint16_t* stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
            uint12_struct pc, uint16_t ir
        ) -> void;
};

class SetRegister : public Command {

    private:
        uint8_t selected_register;
        uint8_t value_to_set;
    
    public:
        SetRegister(uint8_t selected_register, uint8_t value_to_set); 
        auto execute(
            uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], 
            uint16_t* stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
            uint12_struct pc, uint16_t ir
        ) -> void;
};

class AddValueToRegister : public Command {
    private:
        uint8_t selected_register;
        uint8_t value_to_add;

    public:
        AddValueToRegister(uint8_t selected_register, uint8_t value_to_add);
        auto execute(
            uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], 
            uint16_t* stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
            uint12_struct pc, uint16_t ir
        ) -> void;
};

class SetIndexRegister : public Command {
    private:
        uint12_struct i_register_address;
    
    public:
        SetIndexRegister(uint12_struct i_register_address);
        auto execute(
            uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], 
            uint16_t* stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
            uint12_struct pc, uint16_t ir
        ) -> void;
};

class DisplayDraw : public Command {
    private:
        uint8_t register_for_x_coordinate;
        uint8_t register_for_y_coordinate;
        uint8_t drawing_height;

    public:
        DisplayDraw(uint8_t x, uint8_t y, uint8_t height); 
        auto execute(
            uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], 
            uint16_t* stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
            uint12_struct pc, uint16_t ir
        ) -> void;
};

class InvalidCommand : public Command {
    private:
        uint16_t instruction;

    public:
        InvalidCommand(uint16_t instruction); 
        auto execute(
            uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], 
            uint16_t* stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
            uint12_struct pc, uint16_t ir
        ) -> void;
};

#endif