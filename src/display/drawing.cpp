#include "../../include/drawing.h"

void createDisplay() {
    InitWindow(WINDOW_LENGTH, WINDOW_HEIGHT, "CHIP-8");
	SetTargetFPS(60);
}

void updateDisplay() {
	BeginDrawing();
	ClearBackground(RAYWHITE);
    DrawText("Window Draw Success", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
}

void closeDisplay() {
	CloseWindow();
}