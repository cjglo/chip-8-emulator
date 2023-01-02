#include "../include/commands.h"

using namespace std; // TODO: Remove once program is complete, here for testing purposes

auto ClearScreenCommand::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    std::vector<uint16_t>& stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{
    for (int i = 0; i < DISPLAY_HEIGHT; i++)
        for (int j = 0; j < DISPLAY_WIDTH; j++)
            display[i][j] = false;
}

auto PopSubRoutine::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    std::vector<uint16_t>& stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{
    pc->bits = stack.back();
    stack.pop_back();
}

JumpCommand::JumpCommand(uint12_struct address)
{
    this->address = address;
}
auto JumpCommand::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    std::vector<uint16_t>& stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{
    pc->bits = this->address.bits;
}

SubRoutines::SubRoutines(uint12_struct subroutine_address)
{
    this->address = subroutine_address;
}
auto SubRoutines::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    std::vector<uint16_t>& stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{
    stack.push_back(pc->bits);
    pc->bits = this->address.bits;
}

SkipXEqVar::SkipXEqVar(uint8_t register_x, uint8_t conditional_val)
{
    this->register_x = register_x;
    this->conditional_val = conditional_val;
}
auto SkipXEqVar::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    std::vector<uint16_t>& stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{
    if(varRegister[this->register_x] == conditional_val)
        pc->bits += 2;
}

SkipXNotEquVar::SkipXNotEquVar(uint8_t register_x, uint8_t conditional_val)
{
    this->register_x = register_x;
    this->conditional_val = conditional_val;
}
auto SkipXNotEquVar::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    std::vector<uint16_t>& stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{
    if(varRegister[this->register_x] != conditional_val)
        pc->bits += 2;
}

SkipXEquY::SkipXEquY(uint8_t register_x, uint8_t register_y)
{
    this->register_x = register_x;
    this->register_y = register_y;
}
auto SkipXEquY::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    std::vector<uint16_t>& stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{
    if(varRegister[this->register_x] == varRegister[this->register_y])
        pc->bits += 2;
}

SkipXNotEquY::SkipXNotEquY(uint8_t register_x, uint8_t register_y)
{
    this->register_x = register_x;
    this->register_y = register_y;
}
auto SkipXNotEquY::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    std::vector<uint16_t>& stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{
    if(varRegister[this->register_x] != varRegister[this->register_y])
        pc->bits += 2;
}

SetRegister::SetRegister(uint8_t selected_register, uint8_t value_to_set)
{
    this->selected_register = selected_register;
    this->value_to_set = value_to_set;
}
auto SetRegister::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    std::vector<uint16_t>& stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{
    // selected_register should be 4 bits max
    varRegister[selected_register] = value_to_set;
}

LogicAndArithmetic::LogicAndArithmetic(uint8_t x_register, uint8_t y_register, uint8_t operation)
{
    this->x_register = x_register;
    this->y_register = y_register;
    this->operation = operation;
}
auto LogicAndArithmetic::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    std::vector<uint16_t>& stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{

    switch (this->operation)
    {
    case 0x0:    // Set X to Y
        varRegister[x_register] = varRegister[y_register];
        break;
    case 0x1:
        varRegister[x_register] = varRegister[x_register] | varRegister[y_register];
        break;
    case 0x2:
        varRegister[x_register] = varRegister[x_register] & varRegister[y_register];
        break;
    case 0x3:
        varRegister[x_register] = varRegister[x_register] ^ varRegister[y_register];
        break;
    case 0x4:
        if(varRegister[x_register] > 255 - varRegister[y_register])
        {
            varRegister[0xF] = 1;
        }
        else
        {
            varRegister[0xF] = 0;
        }
        varRegister[x_register] = varRegister[x_register] + varRegister[y_register];
        break;
    case 0x5:
        if(varRegister[x_register] <= varRegister[y_register])
        {
            varRegister[0XF] = 1;
        }
        else
        {
            varRegister[0xF] = 0;
        }
        varRegister[x_register] = varRegister[x_register] - varRegister[y_register];
        break;
    case 0x6:
    {
        varRegister[x_register] = varRegister[y_register];
        uint8_t carry = varRegister[x_register] & 0x01; // bit that is shifted out is saved for carry flag
        varRegister[x_register] = varRegister[x_register] >> 1;
        varRegister[0xF] = carry;
        break;
    }
    case 0x7:
        if(varRegister[y_register] <= varRegister[x_register])
        {
            varRegister[0XF] = 1;
        }
        else
        {
            varRegister[0xF] = 0;
        }
        varRegister[x_register] = varRegister[y_register] - varRegister[x_register];
        break;
    case 0xE:
    {
        varRegister[x_register] = varRegister[y_register];
        uint8_t carry = (varRegister[x_register] & 0x80) >> 7; // bit that is shifted out is saved for carry flag
        varRegister[x_register] = varRegister[x_register] << 1;
        varRegister[0xF] = carry;
        break;
    }
    default:
        break;
    }
}

AddValueToRegister::AddValueToRegister(uint8_t selected_register, uint8_t value_to_add)
{
    this->selected_register = selected_register;
    this->value_to_add = value_to_add;
}
auto AddValueToRegister::execute(
    uint8_t *memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH],
    std::vector<uint16_t>& stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
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
    std::vector<uint16_t>& stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
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
    std::vector<uint16_t>& stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
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
    std::vector<uint16_t>& stack, uint8_t varRegister[VARIABLE_REGISTERS_SIZE],
    uint12_struct *pc, uint16_t *ir) -> void
{

    throw std::invalid_argument("InvalidCommand's Execute() Called, instruction value was: " + to_string(this->instruction));
}