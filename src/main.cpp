#include "../include/main.h"

int main() {

    // Initialize all virtual hardware
    uint8_t Memory[MEMORY_SIZE];
    bool Display[DISPLAY_HEIGHT][DISPLAY_WIDTH];
    uint16_t Stack[STACK_SIZE];
    uint8_t DelayTimer = 255;
    uint8_t SoundTimer = 255;
    uint10_struct PC;
    PC.bits = 0;
    uint16_t IRegister = 0;

    createDisplay();

    sleep(5);

    updateDisplay();

    sleep(2);

    closeDisplay();


    // TODO: Init Front Sprite data in Memory between 50...9F

    // begin loop
        // fetch
        // decode
        // execute

    return 0;
}