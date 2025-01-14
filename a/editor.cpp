#include "editor.h"

Editor::Editor()
{
	initCamera();
	initTools();

	resources = ResourceManager::GetInstance();
	
	shader = resources->GetShader(Shaders::EDITOR_SHADER);
	shader->locs[SHADER_LOC_COLOR_AMBIENT] = GetShaderLocation(*shader, "time");

	resources->ResLoadMaterial();
	resources->MaterialAddTexture(Materials::BLOC_MATERIAL, Textures::PILLAR);
	bloc = resources->GetMaterial(Materials::BLOC_MATERIAL);

	resources->ResLoadRenderTexture(GetScreenWidth() / 2 + 100, ImGui::GetMainViewport()->Size.y);
	render = resources->GetRenderTexture(RenderTextures::EDITOR_RENDER); 

	//rlEnableShader(shader->id);
	//std::cout << "shader id: " << shader->id << std::endl;
	//model.materials[0].shader = *shader;
}

void Editor::Draw()
{
	//BeginShaderMode(*shader);
	DrawTexturePro(render->texture, {0, 0, (float)render->texture.width, -(float)render->texture.height}, {GetScreenWidth() * 0.5f - 100, 0, (float)render->texture.width, (float)render->texture.height}, {0, 0}, 0, WHITE);
	DrawRectangleLines(GetScreenWidth() * 0.5f - 100, 0, render->texture.width, -render->texture.height, BLACK);
	//EndShaderMode();

	BeginMode2D(cam);

	drawTiles();

	drawModel();

	EndMode2D();

	if (len > 0)
		DrawText(TextFormat("%d", len), GetMouseX() + 25, GetMouseY(), 20, BLACK);
	if (len2 > 0)
		DrawText(TextFormat("%d", len2), GetMouseX(), GetMouseY() + 25, 20, BLACK);

	drawSaveMenu();
	drawLoadMenu();

	drawTools();

	drawTotals(0, 0);

	DrawText(TextFormat("Tool: %d", tool), 10, GetScreenHeight() - 30, 30, GRAY);

	DrawFPS(10, GetScreenHeight() - 100);
}

void Editor::Update()
{
	SetShaderValue(*shader, shader->locs[SHADER_LOC_COLOR_AMBIENT], &time, SHADER_UNIFORM_FLOAT);

	time = GetTime();
	len = 0;
	len2 = 0;
	UpdateCameraNew(&cam3d, CAMERA_ORBITAL);
	
	updateTiles();

	if (!saveMenu && !loadMenu)
	{
		updateTools();

		data.floors += IsKeyPressed(KEY_UP);
		data.floors -= IsKeyPressed(KEY_DOWN) * (data.floors > 1);
	}

	updateModel();
}

void Editor::BackgroundUpdates()
{
	if (IsWindowResized())
	{
		onWindowResize();
	}
}

void Editor::OnSwitch()
{
	ShowCursor();
	EnableCursor();
}

//******************************
//
//		Private Functions
//
//******************************

// Draw functions

void Editor::drawTotals(int x, int y)
{
	bool p_open = true;
	int flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove;
	
	ImGui::SetNextWindowPos({ 1, 20 }, ImGuiCond_Always, {0, 0});
	
	ImGui::Begin("Resources", &p_open, flags);
	
	ImGui::Text("Stone: %d", data.stoneTotal);
	ImGui::Text("Slabs: %d", data.slabTotal);
	ImGui::Text("Walls: %d", data.wallTotal);
	ImGui::Text("Concrete: %d", data.concreteTotal);
	ImGui::Text("Floors: %d", data.floors - 1);
	ImGui::Text("Total Stone: %d", data.stoneTotal + data.slabTotal / 2 + data.wallTotal);

	ImGui::End();

	// OLD UI:
	//DrawText(TextFormat("Stone: %d", stoneTotal), x + 10, y + 10, 30, GRAY);
	//DrawText(TextFormat("Slabs: %d", slabTotal), x + 10, y + 40, 30, GRAY);
	//DrawText(TextFormat("Walls: %d", wallTotal), x + 10, y + 70, 30, GRAY);
	//DrawText(TextFormat("Concrete: %d", concreteTotal), x + 10, y + 100, 30, GRAY);
	//DrawText(TextFormat("Floors: %d", floors - 1), x + 10, y + 130, 30, GRAY);
	//DrawText(TextFormat("Total Stone: %d", stoneTotal + slabTotal / 2 + wallTotal), x + 190, y + 10, 30, GRAY);

}

void Editor::drawTile(char type, int x, int y)
{
	switch (type)
	{
	case -1:
		DrawRectangleLines(x, y, tileSize, tileSize, GRAY);
		return;
	case 0:
		DrawRectangle(x, y, tileSize, tileSize, RED);
		return;
	case 1:
		DrawRectangle(x, y, tileSize, tileSize, GREEN);
		return;
	}
	DrawRectangle(x, y, tileSize, tileSize, BLUE);
}

void Editor::drawSaveMenu()
{
	bool p_open = saveMenu;

	if (p_open)
	{
		int flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;

		ImGui::SetNextWindowPos({ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }, ImGuiCond_Appearing, { 0, 0 });

		if (ImGui::Begin("Save", &p_open, flags))
		{
			ImGui::InputText("", buf, 32);
			ImGui::SameLine();
			if (ImGui::SmallButton("Save"))
			{
				std::string saveName = ("./saves/");
				saveName += buf;
				saveName += ".txt";
				std::ofstream save(saveName);
				for (int i = 0; i < sizeY; i++)
					for (int j = 0; j < sizeX; j++)
						save << tiles[i][j] << " ";

				save << data.floors;

				p_open = false;
			}
		}

		ImGui::End();

		saveMenu = p_open;
	}

	// OLD UI:
	//DrawRectangle(GetScreenWidth() / 2 - 200, GetScreenHeight() / 2 - 32, 400, 60, { 0, 0, 0, 200 });
	//DrawText("Save name:", GetScreenWidth() / 2 - 190, GetScreenHeight() / 2 - 30, 30, WHITE);
	//DrawText(saveName.c_str(), GetScreenWidth() / 2 - 190, GetScreenHeight() / 2, 20, WHITE);
	//closeSave.DrawButton(true);
}

void Editor::drawLoadMenu()
{
	bool p_open = loadMenu;

	if (p_open)
	{
		int flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;

		ImGui::SetNextWindowPos({ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f - 100 }, ImGuiCond_Appearing, { 0, 0 });

		if (ImGui::Begin("Load", &p_open, flags))
		{
			ImGui::BeginTable("Files", 1);
			for (int i = 0; i < saves.size(); i++)
			{
				ImGui::TableNextColumn();
				ImGui::Separator();
				if (ImGui::Selectable(saves[i].c_str()))
				{
					std::ifstream load(saves[i]);
					for (int j = 0; j < sizeY; j++)
						for (int k = 0; k < sizeX; k++)
							load >> tiles[j][k];

					if (!load.eof())
						load >> data.floors;
				}
			}
			ImGui::EndTable();
		}

		ImGui::End();

		loadMenu = p_open;
	}

	// OLD UI:
	//DrawRectangle(GetScreenWidth() / 2 - 200, 100, 400, GetScreenHeight() - 100, { 0, 0, 0, 200 });
	//DrawText("Pick a save to load", GetScreenWidth() / 2 - 190, 110, 30, WHITE);
	//for (int i = 0; i < saves.size(); i++)
	//{
	//	DrawText(saves[i].c_str(), GetScreenWidth() / 2 - 190, 150 + i * 20, 20, WHITE);
	//}
	//DrawRectangleLines(GetScreenWidth() / 2 - 200, 150 + currentSave * 20, 400, 20, WHITE);
	//closeLoad.DrawButton(true);
}

void Editor::drawTiles()
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			drawTile(tiles[i][j], i * tileSize, j * tileSize);
			drawTile(buffer[i][j], i * tileSize, j * tileSize);
		}
	}
}

void Editor::drawTools()
{
	if (ImGui::Begin("Tools"))
	{
		if (ImGui::Button("Multitool")) tool = Tools::TMULTI;
		if (ImGui::Button("Pencil")) tool = Tools::TPIXEL;
		if (ImGui::Button("Line")) tool = Tools::TLINE;
		if (ImGui::Button("Bucket")) tool = Tools::TFILL;

		ImGui::Text("Current Tool: %d", tool);
	}

	ImGui::End();
}

void Editor::drawModel()
{
	bool p_open = true;
	int flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImVec2 pos = viewport->WorkPos;

	ImGui::SetNextWindowPos({ (float)GetScreenWidth(), pos.y}, ImGuiCond_Always, {1, 0});

	if (ImGui::Begin("Render", &p_open, flags)) 
	{
		rlImGuiImageRenderTexture(render);
	}
	ImGui::End();
}

// Update functions

void Editor::onWindowResize()
{
	resources->ReloadRenderTexture(RenderTextures::EDITOR_RENDER, GetScreenWidth() / 2 + 100, ImGui::GetMainViewport()->Size.y);
}

void Editor::updateModel()
{
	BeginTextureMode(*render);
	ClearBackground(WHITE);

	BeginMode3D(cam3d);

	BeginShaderMode(*shader);

	//for (int i = 0; i < model.meshCount; i++)
	//	DrawMesh(model.meshes[i], *bloc, model.transform);

	DrawModel(model, { 0, 0, 0 }, 1, WHITE);

	//DrawModelWires(model, {0, 0, 0}, 1, BLACK);

	EndShaderMode();

	EndMode3D();

	EndTextureMode();
}

void Editor::updateTiles()
{
	Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), cam);

	if (mouse.x > 0 && mouse.y > 0 && mouse.x < sizeX * tileSize && mouse.y < sizeY * tileSize)
	{

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			updateLeftClickPressed(mouse);
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			updateLeftClickDown(mouse);
		}

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			updateLeftClickRelease();
			model = createSingleModel(tiles, data.floors);
			calculateResources();
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			updateRightClickPressed(mouse);
		}

		if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
		{
			model = createSingleModel(tiles, data.floors);
			calculateResources();
		}
	}
}

void Editor::updateLeftClickRelease()
{
	memset(buffer, -1, sizeof(buffer));

	Vector2 A2 = A, B2 = B;

	if (A2.x > B2.x)
		std::swap(A2.x, B2.x);
	if (A2.y > B2.y)
		std::swap(A2.y, B2.y);

	if (tool == Tools::TMULTI)
	{
		if (A.x == B.x)
		{
			len = std::abs(B2.y - A2.y + 1);
			for (int i = A2.y + 1; i < B2.y; i++)
				tiles[i][(int)A2.x] = 1;
			tiles[(int)B2.y][(int)A2.x] = 0;
		}
		else if (A.y == B.y)
		{
			len = std::abs(B2.x - A2.x + 1);
			for (int i = A2.x + 1; i < B2.x; i++)
				tiles[(int)A2.y][i] = 1;
			tiles[(int)A2.y][(int)B2.x] = 0;
		}
		else
		{
			if (IsKeyDown(KEY_LEFT_SHIFT))
			{
				tiles[(int)A2.y][(int)A2.x] = 0;
				tiles[(int)B2.y][(int)B2.x] = 0;
				tiles[(int)B2.y][(int)A2.x] = 0;
				tiles[(int)A2.y][(int)B2.x] = 0;

				for (int i = A2.x + 1; i < B2.x; i++)
					tiles[(int)A2.y][i] = 1;

				for (int i = A2.y + 1; i < B2.y; i++)
					tiles[i][(int)A2.x] = 1;

				for (int i = A2.x + 1; i < B2.x; i++)
					tiles[(int)B2.y][i] = 1;

				for (int i = A2.y + 1; i < B2.y; i++)
					tiles[i][(int)B2.x] = 1;
			}

			len = std::abs(B2.x - A2.x + 1);
			len2 = std::abs(B2.y - A2.y + 1);
			for (int i = A2.x + 1; i < B2.x; i++)
				for (int j = A2.y + 1; j < B2.y; j++)
					tiles[j][i] = 2;
		}

	}
	else if (tool == Tools::TLINE)
	{
		if (A.x == B.x)
		{
			len = B2.y - A2.y + 1;
			for (int i = A2.y + 1; i < B2.y; i++)
				tiles[i][(int)A2.x] = 1;
		}
		else if (A.y == B.y)
		{
			len = B2.x - A2.x + 1;
			for (int i = A2.x + 1; i < B2.x; i++)
				tiles[(int)A2.y][i] = 1;
		}
	}
}

void Editor::updateLeftClickDown(Vector2& mouse)
{
	memset(buffer, -1, sizeof(buffer));
	int y = mouse.x / tileSize;
	int x = mouse.y / tileSize;
	B = { (float)x, (float)y };

	Vector2 A2 = A, B2 = B;

	if (A2.x > B2.x)
		std::swap(A2.x, B2.x);
	if (A2.y > B2.y)
		std::swap(A2.y, B2.y);

	if (tool == Tools::TMULTI)
	{
		if (A.x == B.x)
		{
			len = B2.y - A2.y + 1;
			for (int i = A2.y + 1; i < B2.y; i++)
				buffer[i][(int)A2.x] = 1;
			buffer[(int)B2.y][(int)A2.x] = 0;
		}
		else if (A.y == B.y)
		{
			len = B2.x - A2.x + 1;
			for (int i = A2.x + 1; i < B2.x; i++)
				buffer[(int)A2.y][i] = 1;
			buffer[(int)A2.y][(int)B2.x] = 0;
		}
		else
		{
			if (IsKeyDown(KEY_LEFT_SHIFT))
			{
				buffer[(int)A2.y][(int)A2.x] = 0;
				buffer[(int)B2.y][(int)B2.x] = 0;
				buffer[(int)B2.y][(int)A2.x] = 0;
				buffer[(int)A2.y][(int)B2.x] = 0;

				for (int i = A2.x + 1; i < B2.x; i++)
					buffer[(int)A2.y][i] = 1;

				for (int i = A2.y + 1; i < B2.y; i++)
					buffer[i][(int)A2.x] = 1;

				for (int i = A2.x + 1; i < B2.x; i++)
					buffer[(int)B2.y][i] = 1;

				for (int i = A2.y + 1; i < B2.y; i++)
					buffer[i][(int)B2.x] = 1;
			}

			len = std::abs(B2.x - A2.x + 1);
			len2 = std::abs(B2.y - A2.y + 1);
			for (int i = A2.x + 1; i < B2.x; i++)
				for (int j = A2.y + 1; j < B2.y; j++)
					buffer[j][i] = 2;
		}

	}
	else if (tool == Tools::TLINE)
	{
		if (A.x == B.x)
		{
			len = B2.y - A2.y + 1;
			for (int i = A2.y + 1; i < B2.y; i++)
				buffer[i][(int)A2.x] = 1;
		}
		else if (A.y == B.y)
		{
			len = B2.x - A2.x + 1;
			for (int i = A2.x + 1; i < B2.x; i++)
				buffer[(int)A2.y][i] = 1;
		}
	}
}

void Editor::updateLeftClickPressed(Vector2& mouse)
{
	int y = (int)(mouse.x / tileSize);
	int x = (int)(mouse.y / tileSize);

	switch (tool)
	{
	case PIXEL:
		tiles[y][x] = selected;
		break;

	case Tools::TLINE:
		A = { (float)x, (float)y };
		break;

	case Tools::TFILL:
		fillDFS(x, y, tiles[y][x], selected, tiles);
		break;

	case Tools::TMULTI:
		tiles[y][x] = selected;
		A = { (float)x, (float)y };
		break;
	}
	model = createSingleModel(tiles, data.floors);
}

void Editor::updateRightClickPressed(Vector2& mouse)
{
	int y = (int)(mouse.x / tileSize);
	int x = (int)(mouse.y / tileSize);
	tiles[y][x] = -1;
}

void Editor::updateTools()
{
	if (IsKeyPressed('S'))
	{
		saveMenu = true;
		loadMenu = false;
	}

	if (IsKeyPressed('L'))
	{
		loadMenu = true;
		saveMenu = false;

		loadSaves();
	}

	if (IsKeyPressed('R'))
	{
		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				tiles[i][j] = -1;
			}
		}
	}

	switch (GetKeyPressed())
	{
	case '1':
		tool = Tools::TPIXEL;
		break;
	case '2':
		tool = Tools::TLINE;
		break;
	case '3':
		tool = Tools::TFILL;
		break;
	case '4':
		tool = Tools::TMULTI;
		break;
	}

	if (IsKeyPressed(KEY_ENTER))
	{
		calculateResources();
	}
}

void Editor::calculateResources()
{
	data.stoneTotal = 0;
	data.wallTotal = 0;
	data.slabTotal = 0;
	data.concreteTotal = 0;
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			if (tiles[i][j] == 0)
				data.stoneTotal += 4 * data.floors;
			else if (tiles[i][j] == 1)
			{
				data.stoneTotal += data.floors;
				if (tiles[i + 1][j] + 1 && tiles[i - 1][j] + 1 && tiles[i][j + 1] + 1 && tiles[i][j - 1] + 1)
					data.wallTotal += 3 * data.floors;
				else
					data.concreteTotal += 3 * data.floors;
			}
			if (tiles[i][j] == 2)
				data.slabTotal += data.floors;
		}
	}
}

void Editor::loadSaves()
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

// Load Functions

void Editor::initTools()
{
	memset(tiles, -1, sizeof(tiles));
	memset(buffer, -1, sizeof(buffer));
}

void Editor::initCamera()
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