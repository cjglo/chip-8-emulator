#include "../../include/drawing.h"

auto createWindow() -> void {
    InitWindow(WINDOW_LENGTH, WINDOW_HEIGHT, "CHIP-8");
	SetTargetFPS(60);
}

auto updateDisplay(bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH]) -> void {
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