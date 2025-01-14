#include "planner.h"

Planner::Planner()
{
	initCamera();
	loadModels();
	for (int i = 0; i < blocs.size(); i++)
	{
		blocs[i].model.materials[0] = LoadMaterialDefault();
		blocs[i].model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("textures/pillar.png");
		blocs[i].info = LoadRenderTexture(300, 200);
	}
}

void Planner::Update()
{
	if (IsKeyPressed('R'))
		loadModels();
	
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		cameraActive = !cameraActive;

		if (!cameraActive)
			DisableCursor();
		else
			EnableCursor();
	}

	UpdateCameraNew(&cam3d, CAMERA_FREE);
}

void Planner::Draw()
{
	drawInfo();
	drawBlocs();
	drawTools();

	DrawFPS(20, 20);
}

void Planner::BackgroundUpdates()
{
	if (IsWindowResized())
		onWindowResize();
}

void Planner::OnSwitch()
{
	saves.clear();
	for (const auto& entry : std::filesystem::directory_iterator("./saves/"))
	{
		if (!entry.is_directory())
		{
			saves.push_back(entry.path().string());
		}
	}
}

// ******************
// 
// Private functions
//
// ******************

void Planner::onWindowResize()
{
	cam.offset = { GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f };
}

void Planner::drawTools()
{
	if (ImGui::Begin("Tools"))
	{
		ImGui::BeginTable("Files", 1);
		for (int i = 0; i < saves.size(); i++)
		{
			ImGui::TableNextColumn();
			ImGui::Separator();
			if (ImGui::Selectable(saves[i].c_str()))
			{
				char tiles[sizeY][sizeX];
				std::ifstream load(saves[i]);
				for (int j = 0; j < sizeY; j++)
					for (int k = 0; k < sizeX; k++)
						load >> tiles[j][k];

				if (!load.eof())
					load >> blocs[i].floors;
			}
		}
		ImGui::EndTable();
	}

	ImGui::End();
}

void Planner::drawBlocs()
{
	float offset = 60.0f;
	BeginMode3D(cam3d);
	for (int i = 0; i < blocs.size(); i++)
	{
		//for (int j = 0; j < blocs[i].meshCount; j++)
		//	DrawMesh(blocs[i].meshes[j], LoadMaterialDefault(), blocs[i].transform);
		DrawModel(blocs[i].model, { i * offset / 2, 0, 0 }, 1, WHITE);
		DrawCubeWires({ i * offset + 20, blocs[i].floors * 2.0f, 20}, 40.0f, blocs[i].floors * 4.0f, 40.0f, PURPLE);
		DrawBillboardPro(cam3d, blocs[i].info.texture, { 0, 0, 300, 200 }, { i * offset, blocs[i].floors * 4.0f, 0 }, { 0, 1, 0 }, { 4, -4 }, { 0, 0 }, 0, GRAY);
		//DrawModelWires(blocs[i], { blocs[i].transform.m3, blocs[i].transform.m7, blocs[i].transform.m11 }, 1, BLACK);
	}
	EndMode3D();
}

void Planner::drawInfo()
{
	for (int i = 0; i < blocs.size(); i++)
	{
		int total = blocs[i].stoneTotal + blocs[i].slabTotal / 2 + blocs[i].wallTotal;

		BeginTextureMode(blocs[i].info);
		
		ClearBackground({80, 80, 80, 180});
		DrawText(TextFormat("Stone: %d", blocs[i].stoneTotal), 10, 10, 30, BLACK);
		DrawText(TextFormat("Slabs: %d", blocs[i].slabTotal), 10, 40, 30, BLACK);
		DrawText(TextFormat("Walls: %d", blocs[i].wallTotal), 10, 70, 30, BLACK);
		DrawText(TextFormat("Concrete: %d", blocs[i].concreteTotal), 10, 100, 30, BLACK);
		DrawText(TextFormat("Floors: %d", blocs[i].floors - 1), 10, 130, 30, BLACK);
		DrawText(TextFormat("Total Stone: %d", total), 10, 160, 30, BLACK);

		EndTextureMode();
	}
}

void Planner::loadModels()
{
	int count = 0;
	for (const auto& entry : std::filesystem::directory_iterator("./saves/"))
	{
		if (!entry.is_directory())
		{
			int floors = 1;
			char tiles[sizeY][sizeX];
			std::ifstream load(entry.path().string());

			for (int i = 0; i < sizeY; i++)
			{
				for (int j = 0; j < sizeX; j++)
				{
					load >> tiles[i][j];
				}
			}

			if (!load.eof())
				load >> floors;

			std::cout << entry.path().string() << std::endl;
			Model model = createSingleModel(tiles, floors, {60.0f * count, 0, 0});
			blocs.push_back({});
			blocs[blocs.size() - 1] = { model, {0}, floors, 0 };
			count++;
		}
	}
}

void Planner::initCamera()
{
	cam.offset = { sizeX * tileSize * 0.25f, sizeY * tileSize * 0.25f };
	cam.rotation = 0;
	cam.target = { 0, 0 };
	cam.zoom = 1;

	cam3d.fovy = 60;
	cam3d.position = { 0.0f, 40, 0.0f };
	cam3d.projection = CAMERA_PERSPECTIVE;
	cam3d.target = { sizeX / 2, 10, sizeY / 2 };
	cam3d.up = { 0, 1, 0 };
}