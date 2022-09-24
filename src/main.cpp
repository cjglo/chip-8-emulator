#include "../include/main.h"

int main() {

    // Initialize all virtual hardware
    uint8_t Memory[MEMORY_SIZE];
    bool Display[DISPLAY_HEIGHT][DISPLAY_WIDTH];
	for(int i = 0; i<DISPLAY_HEIGHT; i++)
		for(int j = 0; j<DISPLAY_WIDTH; j++) {
            Display[i][j] = false;
		}
    uint16_t Stack[STACK_SIZE];
    uint8_t DelayTimer = 255;
    uint8_t SoundTimer = 255;
    uint10_struct PC;
    PC.bits = 0;
    uint16_t IRegister = 0;

    // TODO: Init Front Sprite data in Memory between 50...9F

    createWindow();
    updateDisplay(Display);
    bool shutdownCommandWasCalled = false; // not sure how I feel about this, maybe a better way by calling raylib close

    while(!WindowShouldClose() && !shutdownCommandWasCalled) { // WindowShouldClose is raylib func that returns true on ESC or close button
        // execution loop:
            // fetch
            // decode
            // execute
	
	    // in the future execution will updateDisplay and or close window
	    // for testing I will leave updateDisplay in loop seperate
	    // until ready to build out those instructions
	    updateDisplay(Display);
    }

    CloseWindow();
    return 0;
}
