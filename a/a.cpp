#include "raylib.h"
#include "editor.h"
#include "planner.h"

#define SCENE_COUNT 2

enum Menus
{
	EDITOR,
	PLANNER
};

int main()
{
	SetWindowState(FLAG_WINDOW_RESIZABLE);

	InitWindow(800, 600, "caca");

	SetTargetFPS(60);

	Editor editor;
	Planner planner;

	Scene *scenes[SCENE_COUNT];
	scenes[0] = &editor;
	scenes[1] = &planner;

	int menu = EDITOR;

	while (!WindowShouldClose())
	{
		scenes[menu]->Update();

		for (int i = 0; i < SCENE_COUNT; i++)
			scenes[i]->BackgroundUpdates();

		if (IsKeyPressed('D')) menu++;

		if (menu > SCENE_COUNT - 1) menu = 0;

		BeginDrawing();
		ClearBackground(WHITE);

		scenes[menu]->Draw();

		EndDrawing();
	}
	CloseWindow();
}