#include "../include/main.h"

int main() {
    // Initialize all virtual hardware
    uint8_t Memory[MEMORY_SIZE];
    initializeMemory(Memory);
    bool Display[DISPLAY_HEIGHT][DISPLAY_WIDTH];
    uint8_t fontData[FONT_DATA_SIZE] = FONT_DATA;
    initializeFontInMemory(Memory, fontData);

    uint16_t Stack[STACK_SIZE];
    uint8_t DelayTimer = 255;
    uint8_t SoundTimer = 255;
    uint12_struct PC;
    PC.bits = STARTING_REGISTER;
    uint16_t IRegister = 0;

    // Set Diplay to blank
	for(int i = 0; i<DISPLAY_HEIGHT; i++)
		for(int j = 0; j<DISPLAY_WIDTH; j++) {
            Display[i][j] = false;
		}

    // TODO: Init Front Sprite data in Memory between 50...9F

    createWindow();
    updateDisplay(Display);
    bool shutdownCommandWasCalled = false; // not sure how I feel about this, maybe a better way by calling raylib close

    while(!WindowShouldClose() && !shutdownCommandWasCalled) { // WindowShouldClose is raylib func that returns true on ESC or close button
        // execution loop:
            // fetch
            uint16_t instruction = fetch(PC, Memory);
            
            // decode
            // execute
	
	    // in the future execution will updateDisplay and or close window
	    // for testing I will leave updateDisplay in loop seperate
	    // until ready to build out those instructions
	    updateDisplay(Display);
	    sleep(CLOCK_EXECUTION_DELAY); 
    }

    CloseWindow();
    return 0;
}

void initializeFontInMemory(uint8_t memory[MEMORY_SIZE], uint8_t fontData[FONT_DATA_SIZE]) {
    for(int i = 0; i<FONT_DATA_SIZE; i++) {
        memory[i+FONT_DATA_START] = fontData[i];
    }
}

void initializeMemory(uint8_t memory[MEMORY_SIZE]) {
    // TODO: Load program here I believe
}