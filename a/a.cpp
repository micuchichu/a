#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>

#define POINT_RADIUS 10

int main()
{
<<<<<<< HEAD
<<<<<<< HEAD
	InitWindow(1080, 1080, "caca");

	Texture2D arena = LoadTexture("./textures/arena.png");
=======
=======
>>>>>>> parent of 1037193 (pull)
	SetWindowState(FLAG_WINDOW_RESIZABLE);
>>>>>>> parent of 1037193 (pull)

	std::vector<Vector2> points;
	Vector2* selected = nullptr;
	Vector2* path = nullptr;
	int pathLen = 0;

	SetTargetFPS(60);

<<<<<<< HEAD
=======
	rlImGuiSetup(true);

	ImGuiStyleSetup();

	LoadTextures();

	Scene* scenes[SCENE_COUNT];
	scenes[0] = new Editor;
	scenes[1] = new Planner;

	int menu = EDITOR;

>>>>>>> parent of 1037193 (pull)
	while (!WindowShouldClose())
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			for (auto& i : points)
			{
				if (Vector2Distance(GetMousePosition(), i) <= 20)
				{
					selected = &i;
					break;
				}
				selected = nullptr;
			}
			
			if(selected == nullptr)
				points.push_back(GetMousePosition());
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			if(selected != nullptr)
				*selected = GetMousePosition();
		}

		if (IsKeyPressed(KEY_DELETE))
		{
			for (int i = 0; i < points.size(); i++)
			{
				if (&points[i] == selected) 
				{
					points.erase(points.begin() + i);
					selected = nullptr;
				}
			}
		}

		BeginDrawing();
		ClearBackground(WHITE);

		DrawTexture(arena, 0, 0, WHITE);
	
		for (auto& i : points)
		{
			DrawCircleV(i, 10, GREEN);
			if (selected == &i)
				DrawCircleV(i, 10, {255, 255, 255, 120});
		}

		for (int i = 0; i < points.size() - 1 && points.size() >= 2; i++)
		{
			DrawLineV(points[i], points[i + 1], GREEN);
			//DrawSplineBezierQuadratic(path, pathLen, 4, GREEN);
		}
	
		EndDrawing();
	}

	CloseWindow();
}