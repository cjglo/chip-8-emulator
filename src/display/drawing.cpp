#include "../../include/drawing.h"

void createDisplay() {
    InitWindow(WINDOW_LENGTH, WINDOW_HEIGHT, "CHIP-8");
	SetTargetFPS(60);
}

void updateDisplay(bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH]) {
	BeginDrawing();
	ClearBackground(BLACK);
    // DrawText("Window Draw Success", 190, 200, 20, LIGHTGRAY);

	// TODO: Draw grid
	DrawGrid(100, 50);

	// Fill in grid
	for(int i = 0; i<DISPLAY_HEIGHT; i++)
		for(int j = 0; j<DISPLAY_WIDTH; j++) {

			if(display[i][j]) {

			}

		}

    EndDrawing();
}

void closeDisplay() {
	CloseWindow();
}