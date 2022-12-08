#include "../include/commands.h"

using namespace std; // TODO: Remove once program is complete, here for testing purposes

auto ClearScreenCommand::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    uint16_t *stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{
    for (int i = 0; i < DISPLAY_HEIGHT; i++)
        for (int j = 0; j < DISPLAY_WIDTH; j++)
            display[i][j] = false;
}

JumpCommand::JumpCommand(uint12_struct address)
{
    this->address = address;
}
auto JumpCommand::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    uint16_t *stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{
    pc->bits = this->address.bits;
}

SetRegister::SetRegister(uint8_t selected_register, uint8_t value_to_set)
{
    this->selected_register = selected_register;
    this->value_to_set = value_to_set;
}
auto SetRegister::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    uint16_t *stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{
    // selected_register should be 4 bits max
    varRegister[selected_register] = value_to_set;
}

AddValueToRegister::AddValueToRegister(uint8_t selected_register, uint8_t value_to_add)
{
    this->selected_register = selected_register;
    this->value_to_add = value_to_add;
}
auto AddValueToRegister::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    uint16_t *stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{
    varRegister[selected_register] += value_to_add;
}

SetIndexRegister::SetIndexRegister(uint12_struct i_register_address)
{
    this->i_register_address = i_register_address;
}
auto SetIndexRegister::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    uint16_t *stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{
    *ir = this->i_register_address.bits;
}

DisplayDraw::DisplayDraw(uint8_t x, uint8_t y, uint8_t height)
{
    this->register_for_x_coordinate = x;
    this->register_for_y_coordinate = y;
    this->drawing_height = height;
}
auto DisplayDraw::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    uint16_t *stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{
    // modulo with screen demensions because values can wrap around
    const uint8_t x = varRegister[this->register_for_x_coordinate] % DISPLAY_WIDTH;
    const uint8_t y = varRegister[this->register_for_y_coordinate] % DISPLAY_HEIGHT;
    // VF flag set to 0
    varRegister[0xF] = 0;

    for(int i = 0; i<this->drawing_height; i++) {
        uint8_t spriteByte = memory[*ir + i];

        // stop if hit bottom edge of screen
        if(i + y >= DISPLAY_HEIGHT)
            break;

        for(int j = 0; j<SPRITE_WIDTH; j++) {

            // if reach end of screen, stop this row
            if(j + x >= DISPLAY_WIDTH)
                break;

            if(display[y + i][j + x] && (spriteByte & (1 << 7 - j))) {
                varRegister[0xF] = 1;
                display[y + i][j + x] = 0;
            } 
            else if(!display[y + i][j + x] && (spriteByte & (1 << 7 - j))) {
                display[y + i][j + x] = 1;
            }
        }
    }

    updateDisplay(display);
}

InvalidCommand::InvalidCommand(uint16_t instruction)
{
    this->instruction = instruction;
}
auto InvalidCommand::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    uint16_t *stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{

    throw std::invalid_argument("InvalidCommand's Execute() Called, instruction value was: " + to_string(this->instruction));
}