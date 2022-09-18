void createDisplay() {
    InitWindow(WINDOW_LENGTH, WINDOW_HEIGHT, "Space Invader");
	SetTargetFPS(60);

	while (!WindowShouldClose()) { // detects ESC key or Window Close Button

		BeginDrawing();
		ClearBackground(RAYWHITE);
                DrawText("Window Draw Success", 190, 200, 20, LIGHTGRAY);
                EndDrawing();
	}
	CloseWindow();
}