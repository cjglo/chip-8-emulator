#include "../../include/drawing.h"

void createWindow() {
    InitWindow(WINDOW_LENGTH, WINDOW_HEIGHT, "CHIP-8");
	SetTargetFPS(60);
}

// NOTE: depricated func, could leave so can test, but clear screen works so not needed?
void updateDisplay(bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH]) {
	BeginDrawing();
	ClearBackground(BLACK);
	for(int i = 0; i<DISPLAY_HEIGHT; i++)
		for(int j = 0; j<DISPLAY_WIDTH; j++) {

			if(display[i][j]) {
				DrawRectangle(j*10, i*10, 10, 10, WHITE);
			}

		}
    EndDrawing();
}