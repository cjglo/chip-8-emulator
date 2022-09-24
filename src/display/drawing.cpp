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

			if(i < j) {
				display[i][j] = true;
			} else {
				display[i][j] = false;
			}

		}


	for(int i = 0; i<DISPLAY_HEIGHT; i++)
		for(int j = 0; j<DISPLAY_WIDTH; j++) {

			if(display[i][j]) {
				DrawRectangle(j*10, i*10, 10, 10, WHITE);
			}

		}

    EndDrawing();
}

void closeDisplay() {
	CloseWindow();
}
