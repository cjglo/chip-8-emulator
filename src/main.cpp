#include "../include/main.h"

int main()
{
    // Initialize all virtual hardware
    uint8_t Memory[MEMORY_SIZE]; // Memory
    initializeMemory(Memory);
    bool Display[DISPLAY_HEIGHT][DISPLAY_WIDTH];  // Display
    uint8_t fontData[FONT_DATA_SIZE] = FONT_DATA; // Font
    initializeFontInMemory(Memory, fontData);
    uint16_t Stack[STACK_SIZE]; // Stack
    uint8_t DelayTimer = 255;   // Delay Timer
    uint8_t SoundTimer = 255;   // Sound Timer
    bool delayTimerOnSwitch = true;
    bool soundTimerOnSwitch = true;
    uint12_struct PC; // Program Counter
    PC.bits = STARTING_REGISTER;
    uint16_t IR = 0;                               // Index Register
    uint8_t varRegisters[VARIABLE_REGISTERS_SIZE]; // Variable Registers

    // Starting timers, they execute independent of exec cycle
    std::thread delayTimerRoutine(delayTimerCycle, &DelayTimer, &delayTimerOnSwitch);
    std::thread soundTimerRoutine(soundTimerCycle, &SoundTimer, &soundTimerOnSwitch);

    createWindow();

    while (!WindowShouldClose())
    {   // WindowShouldClose is raylib func that returns true on ESC or close button
        // execution loop:
        // fetch
        uint16_t instruction = fetch(PC, Memory);

        // decode
        std::unique_ptr<Command> command = decode(instruction);

        // execute
        command->execute(Memory, Display, Stack, varRegisters, &PC, &IR);

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

auto initializeFontInMemory(uint8_t memory[MEMORY_SIZE], uint8_t fontData[FONT_DATA_SIZE]) -> void
{
    for (int i = 0; i < FONT_DATA_SIZE; i++)
    {
        memory[i + FONT_DATA_START] = fontData[i];
    }
}

auto initializeMemory(uint8_t memory[MEMORY_SIZE]) -> void
{
    // TODO: Load program here I believe
    // FOR TESTING
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        memory[i] = (i % 2 == 0) ? 0xAF : 0x12;
    }
}

// NOTE: Timers are currently dependent on WindowShouldClose, which is external.  Maybe should pass as parameter?
auto delayTimerCycle(uint8_t *timer, bool *onSwitch) -> void
{
    while (true)
    {
        sleep(TIMER_DELAY);
        if (*timer == 0)
        {
            *timer = 255;
        }
        else
        {
            *timer -= 1;
        }
        if (!*onSwitch)
            break;
    }
}

auto soundTimerCycle(uint8_t *timer, bool *onSwitch) -> void
{
    while (true)
    {
        sleep(TIMER_DELAY);
        if (*timer == 0)
        {
            *timer = 255;
        }
        else
        {
            // TODO: Play Sound
            *timer -= 1;
        }
        if (!*onSwitch)
            break;
    }
}