#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include <vector>

#include "const.h"
#include "drawing.h"
#include <stdint.h>

// testing and debugging
#define UNIMPLEMENTED_COMMAND_DEBUG_CALL std::cout << "UNIMPLEMENTED COMMAND CALLED" << std::endl;

// abstract Commmand Class
class Command
{
public:
    virtual auto execute(
        uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
        std::vector<uint16_t>& stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
        uint12_struct *pc, uint16_t *ir) -> void = 0;
};

// all instruction classes
class ClearScreenCommand : public Command
{
public:
    auto execute(
        uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
        std::vector<uint16_t>& stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
        uint12_struct *pc, uint16_t *ir) -> void;
};

class PopSubRoutine : public Command
{
public:
    auto execute(
        uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
        std::vector<uint16_t>& stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
        uint12_struct *pc, uint16_t *ir) -> void;
};

class JumpCommand : public Command
{
private:
    uint12_struct address;

public:
    JumpCommand(uint12_struct address);
    auto execute(
        uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
        std::vector<uint16_t>& stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
        uint12_struct *pc, uint16_t *ir) -> void;
};

class SubRoutines : public Command
{
private:
    uint12_struct address;

public:
    SubRoutines(uint12_struct subroutine_address);

    auto execute(
        uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
        std::vector<uint16_t>& stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
        uint12_struct *pc, uint16_t *ir) -> void;
};

class SkipXEqVar : public Command
{
private:
    uint8_t register_x;
    uint8_t conditional_val;
public:
    SkipXEqVar(uint8_t register_x, uint8_t conditional_val);
    auto execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    std::vector<uint16_t>& stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void;
};

class SkipXNotEquVar : public Command
{
private:
    uint8_t register_x;
    uint8_t conditional_val;
public:
    SkipXNotEquVar(uint8_t register_x, uint8_t conditional_val);
    auto execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    std::vector<uint16_t>& stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void;
};

class SkipXEquY : public Command
{
private:
    uint8_t register_x;
    uint8_t register_y;
public:
    SkipXEquY(uint8_t register_x, uint8_t register_y);
    auto execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    std::vector<uint16_t>& stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void;
};

class SkipXNotEquY : public Command
{
private:
    uint8_t register_x;
    uint8_t register_y;
public:
    SkipXNotEquY(uint8_t register_x, uint8_t register_y);
    auto execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    std::vector<uint16_t>& stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void;
};

class SetRegister : public Command
{
private:
    uint8_t selected_register;
    uint8_t value_to_set;

public:
    SetRegister(uint8_t selected_register, uint8_t value_to_set);
    auto execute(
        uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
        std::vector<uint16_t>& stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
        uint12_struct *pc, uint16_t *ir) -> void;
};

class AddValueToRegister : public Command
{
private:
    uint8_t selected_register;
    uint8_t value_to_add;

public:
    AddValueToRegister(uint8_t selected_register, uint8_t value_to_add);
    auto execute(
        uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
        std::vector<uint16_t>& stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
        uint12_struct *pc, uint16_t *ir) -> void;
};

class LogicAndArithmetic : public Command
{
private:
    uint8_t operation;
    uint8_t x_register;
    uint8_t y_register;
public:
    LogicAndArithmetic(uint8_t x_register, uint8_t y_register, uint8_t operation);
    auto execute(
        uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
        std::vector<uint16_t>& stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
        uint12_struct *pc, uint16_t *ir) -> void;
};

class SetIndexRegister : public Command
{
private:
    uint12_struct i_register_address;

public:
    SetIndexRegister(uint12_struct i_register_address);
    auto execute(
        uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
        std::vector<uint16_t>& stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
        uint12_struct *pc, uint16_t *ir) -> void;
};

class DisplayDraw : public Command
{
private:
    uint8_t register_for_x_coordinate;
    uint8_t register_for_y_coordinate;
    uint8_t drawing_height;

public:
    DisplayDraw(uint8_t x, uint8_t y, uint8_t height);
    auto execute(
        uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
        std::vector<uint16_t>& stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
        uint12_struct *pc, uint16_t *ir) -> void;
};

class InvalidCommand : public Command
{
private:
    uint16_t instruction;

public:
    InvalidCommand(uint16_t instruction);
    auto execute(
        uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
        std::vector<uint16_t>& stack, uint8_t varRegisters[VARIABLE_REGISTERS_SIZE],
        uint12_struct *pc, uint16_t *ir) -> void;
};

#endif