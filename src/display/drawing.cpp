#include "../../include/drawing.h"

void createDisplay() {
    InitWindow(WINDOW_LENGTH, WINDOW_HEIGHT, "CHIP-8");
	SetTargetFPS(60);
}

void updateDisplay(bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH]) {
	BeginDrawing();
	ClearBackground(BLACK);
    // DrawText("Window Draw Success", 190, 200, 20, LIGHTGRAY);

	for(int i = 0; i<DISPLAY_HEIGHT; i++)
		for(int j = 0; j<DISPLAY_WIDTH; j++) {

			if(display[i][j]) {
				DrawRectangle(WINDOW_LENGTH/2, WINDOW_HEIGHT/2, 30, 30, MAROON);
			}

		}

    EndDrawing();
}

void closeDisplay() {
	CloseWindow();
}