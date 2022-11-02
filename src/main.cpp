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
    bool delayTimerOnSwitch = true;
    bool soundTimerOnSwitch = true;
    uint12_struct PC;
    PC.bits = STARTING_REGISTER;
    uint16_t IRegister = 0;

    // Set Diplay to blank
	for(int i = 0; i<DISPLAY_HEIGHT; i++)
		for(int j = 0; j<DISPLAY_WIDTH; j++) {
            Display[i][j] = false;
		}
    
    // Starting timers, they execute independent of exec cycle
    std::thread delayTimerRoutine(delayTimerCycle, &DelayTimer, &delayTimerOnSwitch);
    std::thread soundTimerRoutine(soundTimerCycle, &SoundTimer, &soundTimerOnSwitch);

    createWindow();
    updateDisplay(Display);

    while(!WindowShouldClose()) { // WindowShouldClose is raylib func that returns true on ESC or close button
        // execution loop:
            // fetch
            uint16_t instruction = fetch(PC, Memory);
            
            // decode
            std::unique_ptr<Command> command = decode(instruction);

            // execute
            command->execute(Memory, Display, Stack, PC, IRegister);
	
	    // in the future execution will updateDisplay and or close window
	    // for testing I will leave updateDisplay in loop seperate
	    // until ready to build out those instructions
	    updateDisplay(Display);
	    sleep(CLOCK_EXECUTION_DELAY); 
    }
    // allow timers to finish so not abrupt abort
    delayTimerOnSwitch = false;
    soundTimerOnSwitch = false;
    delayTimerRoutine.join();
    soundTimerRoutine.join();

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
    // FOR TESTING (Calls jump command, unimplemented)
    for(int i = 0; i<MEMORY_SIZE; i++) {

        memory[i] = (i % 2 == 0) ? 0x1F : 0xFF;

    }
}

// NOTE: Timers are currently dependent on WindowShouldClose, which is external.  Maybe should pass as parameter?
void delayTimerCycle(uint8_t* timer, bool* onSwitch) {
    while(true) {
        sleep(TIMER_DELAY);
        if(*timer == 0) {
            *timer = 255;
        } else {
            *timer -= 1;
        }
        if(!*onSwitch) break;
    }
}

void soundTimerCycle(uint8_t* timer, bool* onSwitch) {
    while(true) {
        sleep(TIMER_DELAY);
        if(*timer == 0) {
            *timer = 255;
        } else {
            // TODO: Play Sound
            *timer -= 1;
        }
        if(!*onSwitch) break;
    }
}