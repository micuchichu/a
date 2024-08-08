#include "planner.h"

Planner::Planner()
{
	initCamera();
	loadModels();
}

void Planner::Update()
{
	if (IsKeyPressed('R'))
		loadModels();

	UpdateCameraNew(&cam3d, CAMERA_FREE);
}

void Planner::Draw()
{
	BeginMode3D(cam3d);
	for (int i = 0; i < blocs.size(); i++)
		for (int j = 0; j < blocs[i].meshCount; j++)
			DrawMesh(blocs[i].meshes[j], LoadMaterialDefault(), blocs[i].transform);
	EndMode3D();
}

void Planner::BackgroundUpdates()
{
	if (IsWindowResized())
		onWindowResize();
}

void Planner::OnSwitch()
{
	HideCursor();
	DisableCursor();
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
			Model model = createSingleModel(tiles, floors, {40.0f * count, 0, 0});
			blocs.push_back(model);
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

	cam3d.fovy = 45;
	cam3d.position = { 0.0f, 40, 0.0f };
	cam3d.projection = CAMERA_PERSPECTIVE;
	cam3d.target = { sizeX / 2, 10, sizeY / 2 };
	cam3d.up = { 0, 1, 0 };
}