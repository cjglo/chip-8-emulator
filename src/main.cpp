#include "../include/main.h"

int main(int argc, char* argv[])
{
    // Initialize all virtual hardware
    uint8_t Memory[MEMORY_SIZE];                    // Memory
    bool Display[DISPLAY_HEIGHT][DISPLAY_WIDTH];    // Display
    uint8_t fontData[FONT_DATA_SIZE] = FONT_DATA;   // Font
    initializeFontInMemory(Memory, fontData);
    uint16_t Stack[STACK_SIZE];                     // Stack
    uint8_t DelayTimer = 255;                       // Delay Timer
    uint8_t SoundTimer = 255;                       // Sound Timer
    bool delayTimerOnSwitch = true;                 // bool that stops delay timer
    bool soundTimerOnSwitch = true;                 // bool that stops sound timer
    uint12_struct PC;                               // Program Counter
    PC.bits = STARTING_REGISTER;
    uint16_t IR = 0;                                // Index Register
    uint8_t varRegisters[VARIABLE_REGISTERS_SIZE];  // Variable Registers

    for (int i = 0; i < DISPLAY_HEIGHT; i++)
        for (int j = 0; j < DISPLAY_WIDTH; j++)
            Display[i][j] = false;

    // Read in Program from file in command line arguement
    initializeMemory(argc, argv, Memory);

    // Starting timers, they execute independent of exec cycle
    std::thread delayTimerRoutine(delayTimerCycle, &DelayTimer, &delayTimerOnSwitch);
    std::thread soundTimerRoutine(soundTimerCycle, &SoundTimer, &soundTimerOnSwitch);

    createWindow();

    while (!WindowShouldClose())
    {   // WindowShouldClose is raylib func that returns true on ESC or close button
        // ---- execution loop ----
        // fetch
        uint16_t instruction = fetch(PC, Memory);

        // decode
        std::unique_ptr<Command> command = decode(instruction);

        // execute
        command->execute(Memory, Display, Stack, varRegisters, &PC, &IR);

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

auto initializeMemory(int argc, char** argv, uint8_t memory[MEMORY_SIZE]) -> void
{
    std::ifstream program;

    if(argc > 1) {
        // TODO: Load in Program
        std::cout << "COMMAND LINE ARGUEMENTS ARE CURRENTLY NOT IMPLEMENTED!" << std::endl;
        exit(1);
    } else {
        // defaults to IBM Program if no agruement passed
        program = std::ifstream(DEFAULT_PROG_FILE_NAME, std::ios::binary | std::ios::ate);
    }

    std::streampos size = program.tellg();
    char* buffer = new char[size];
    program.seekg(0, std::ios::beg);
    program.read(buffer, size);
    program.close();

    for(int i = 0; i<size; i++) {
        memory[STARTING_REGISTER + i] = buffer[i];
    }

    delete[] buffer; 
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