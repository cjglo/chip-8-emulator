#include "../include/commands.h"

using namespace std;

void ClearScreenCommand::execute(uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], uint16_t* stack, uint12_struct pc, uint16_t ir) {
    UNIMPLEMENTED_COMMAND_DEBUG_CALL
}

JumpCommand::JumpCommand(uint16_t instruction) {
    uint12_struct address;
    address.bits = instruction; // only 3 least significant bytes saved, last byte is removed
    this->address = address;
}
void JumpCommand::execute(uint8_t* memory, bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH], uint16_t* stack, uint12_struct pc, uint16_t ir) {
    cout<<"JUMPCOMMAND"<<endl;
    UNIMPLEMENTED_COMMAND_DEBUG_CALL
}