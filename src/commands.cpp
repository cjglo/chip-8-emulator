#include "../include/commands.h"

using namespace std; // TODO: Remove after testing

auto ClearScreenCommand::execute(
    uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], 
    uint16_t* stack, uint12_struct pc, uint16_t ir
) -> void {
      for(int i = 0; i<DISPLAY_HEIGHT; i++)
        for(int j = 0; j<DISPLAY_WIDTH; j++) 
            display[i][j] = false;
}

JumpCommand::JumpCommand(uint12_struct address) {
    this->address = address;
}
auto JumpCommand::execute(
    uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], 
    uint16_t* stack, uint12_struct pc, uint16_t ir
) -> void {
    cout<<"JUMPCOMMAND: "<<this->address.bits<<endl;
    UNIMPLEMENTED_COMMAND_DEBUG_CALL
}

SetRegister::SetRegister(uint8_t selected_register, uint8_t value_to_set) {
    this->selected_register = selected_register;
    this->value_to_set = value_to_set;
}
auto SetRegister::execute(
    uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], 
    uint16_t* stack, uint12_struct pc, uint16_t ir
) -> void {
    cout<<"SET REGISTER COMMAND"<<endl;
    UNIMPLEMENTED_COMMAND_DEBUG_CALL
}

AddValueToRegister::AddValueToRegister(uint8_t selected_register, uint8_t value_to_add) {
    this->selected_register = selected_register;
    this->value_to_add = value_to_add;
}
auto AddValueToRegister::execute(
    uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], 
    uint16_t* stack, uint12_struct pc, uint16_t ir
) -> void {
    cout<<"ADD REGISTER COMMAND"<<endl;
    UNIMPLEMENTED_COMMAND_DEBUG_CALL
}

SetIndexRegister::SetIndexRegister(uint12_struct i_register_address) {
    this->i_register_address = i_register_address;
}
auto SetIndexRegister::execute(
    uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], 
    uint16_t* stack, uint12_struct pc, uint16_t ir
) -> void {
    cout<<"Set Index Register"<<endl;
    UNIMPLEMENTED_COMMAND_DEBUG_CALL
}

DisplayDraw::DisplayDraw(uint8_t x, uint8_t y, uint8_t height) {
    this->register_for_x_coordinate = x;
    this->register_for_y_coordinate = y;
    this->drawing_height = height;
}
auto DisplayDraw::execute(
    uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], 
    uint16_t* stack, uint12_struct pc, uint16_t ir
) -> void {
    cout<<"Display/Draw"<<endl;
    UNIMPLEMENTED_COMMAND_DEBUG_CALL
}

InvalidCommand::InvalidCommand(uint16_t instruction) {
    this->instruction = instruction;
}
auto InvalidCommand::execute(
    uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], 
    uint16_t* stack, uint12_struct pc, uint16_t ir
) -> void {
    
    throw std::invalid_argument("Invalid Command's Execute Called, instruction value was: " + to_string(this->instruction));
}