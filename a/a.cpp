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
	std::cout << "Editor size: " << sizeof(Editor) << std::endl;
	std::cout << "Planner size: " << sizeof(Planner) << std::endl;

	SetWindowState(FLAG_WINDOW_RESIZABLE);

	InitWindow(800, 600, "caca");

	SetTargetFPS(60);

	rlImGuiSetup(true);

	ImGuiStyleSetup();

	LoadTextures();
	LoadShaders();
	LoadRenderTextures();

	Scene* scenes[SCENE_COUNT];
	scenes[0] = new Editor;
	scenes[1] = new Planner;

	int menu = EDITOR;

	while (!WindowShouldClose())
	{
		scenes[menu]->Update();

		for (int i = 0; i < SCENE_COUNT; i++)
			scenes[i]->BackgroundUpdates();

		//if (IsKeyPressed('N'))
		//{
		//	//menu++;
		//	scenes[menu]->OnSwitch();
		//}
		//if (menu > SCENE_COUNT - 1) menu = 0;

		BeginDrawing();
		ClearBackground(WHITE);
		rlImGuiBegin();

		ImGui::BeginMainMenuBar();

		if (ImGui::MenuItem("Editor")) 
		{ 
			menu = EDITOR;
			scenes[menu]->OnSwitch();
		}

		if (ImGui::MenuItem("Planner"))
		{
			menu = PLANNER;
			scenes[menu]->OnSwitch();
		}

		ImGui::EndMainMenuBar();

		//ImGui::ShowDemoWindow();
		scenes[menu]->Draw();

		rlImGuiEnd();

		EndDrawing();
	}
	CloseWindow();
}