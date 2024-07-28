#include "editor.h"

Editor::Editor()
{
	initCamera();
	initTools();
}

void Editor::Draw()
{
	DrawTexturePro(view3D.texture, { 0, 0, (float)view3D.texture.width, -(float)view3D.texture.height }, { GetScreenWidth() * 0.5f - 100, 0, (float)view3D.texture.width, (float)view3D.texture.height }, { 0, 0 }, 0, WHITE);

	BeginMode2D(cam);

	drawTiles();

	EndMode2D();

	if (len > 0)
		DrawText(TextFormat("%d", len), GetMouseX() + 25, GetMouseY(), 20, BLACK);
	if (len2 > 0)
		DrawText(TextFormat("%d", len2), GetMouseX(), GetMouseY() + 25, 20, BLACK);

	if (saveMenu)
	{
		drawSaveMenu();
	}
	else if (loadMenu)
	{
		drawLoadMenu();
	}

	for (int i = 0; i < 4; i++)
		tools[i].DrawButton();

	for (int i = 0; i < 3; i++)
		build[i].DrawButton(0.2f);

	drawTotals(0, 0);

	DrawText(TextFormat("Tool: %d", tool), 10, GetScreenHeight() - 30, 30, GRAY);

	DrawFPS(10, GetScreenHeight() - 100);
}

void Editor::Update()
{
	len = 0;
	len2 = 0;
	UpdateCamera(&cam3d);
	
	updateTiles();

	for (int i = 0; i < 4; i++)
		tools[i].Clicked();

	for (int i = 0; i < 3; i++)
		build[i].Clicked();

	if (!saveMenu && !loadMenu)
	{
		updateTools();

		floors += IsKeyPressed(KEY_UP);
		floors -= IsKeyPressed(KEY_DOWN) * (floors > 1);
	}
	else if (loadMenu)
	{
		updateLoadMenu();
	}
	else if (saveMenu)
	{
		updateSaveMenu();
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

//******************************
//
//		Private Functions
//
//******************************

// Draw functions

void Editor::drawTotals(int x, int y)
{
	DrawText(TextFormat("Stone: %d", stoneTotal), x + 10, y + 10, 30, GRAY);
	DrawText(TextFormat("Slabs: %d", slabTotal), x + 10, y + 40, 30, GRAY);
	DrawText(TextFormat("Walls: %d", wallTotal), x + 10, y + 70, 30, GRAY);
	DrawText(TextFormat("Concrete: %d", concreteTotal), x + 10, y + 100, 30, GRAY);
	DrawText(TextFormat("Floors: %d", floors - 1), x + 10, y + 130, 30, GRAY);
	DrawText(TextFormat("Total Stone: %d", stoneTotal + slabTotal / 2 + wallTotal), x + 190, y + 10, 30, GRAY);
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
	DrawRectangle(GetScreenWidth() / 2 - 200, GetScreenHeight() / 2 - 32, 400, 60, { 0, 0, 0, 200 });
	DrawText("Save name:", GetScreenWidth() / 2 - 190, GetScreenHeight() / 2 - 30, 30, WHITE);
	DrawText(saveName.c_str(), GetScreenWidth() / 2 - 190, GetScreenHeight() / 2, 20, WHITE);
	closeSave.DrawButton(true);
}

void Editor::drawLoadMenu()
{
	DrawRectangle(GetScreenWidth() / 2 - 200, 100, 400, GetScreenHeight() - 100, { 0, 0, 0, 200 });
	DrawText("Pick a save to load", GetScreenWidth() / 2 - 190, 110, 30, WHITE);

	for (int i = 0; i < saves.size(); i++)
	{
		DrawText(saves[i].c_str(), GetScreenWidth() / 2 - 190, 150 + i * 20, 20, WHITE);
	}
	DrawRectangleLines(GetScreenWidth() / 2 - 200, 150 + currentSave * 20, 400, 20, WHITE);
	closeLoad.DrawButton(true);
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

// Update functions

void Editor::onWindowResize()
{
	tools[0].setPos(GetScreenWidth() - 30, GetScreenHeight() / 2 - 45);
	tools[1].setPos(GetScreenWidth() - 30, GetScreenHeight() / 2 - 15);
	tools[2].setPos(GetScreenWidth() - 30, GetScreenHeight() / 2 + 15);
	tools[3].setPos(GetScreenWidth() - 30, GetScreenHeight() / 2 + 45);

	build[0].setPos(GetScreenWidth() / 2 - 32, GetScreenHeight() - 32);
	build[1].setPos(GetScreenWidth() / 2, GetScreenHeight() - 32);
	build[2].setPos(GetScreenWidth() / 2 + 32, GetScreenHeight() - 32);

	closeSave.setPos(GetScreenWidth() / 2 + 180, GetScreenHeight() / 2 - 32);
	closeLoad.setPos(GetScreenWidth() / 2 + 180, 100);

	view3D = LoadRenderTexture(GetScreenWidth() / 2 + 100, GetScreenHeight());
}

void Editor::updateModel()
{
	BeginTextureMode(view3D);
	ClearBackground(WHITE);

	BeginMode3D(cam3d);

	for (int i = 0; i < model.meshCount; i++)
		DrawMesh(model.meshes[i], LoadMaterialDefault(), model.transform);

	EndMode3D();

	EndTextureMode();
}

void Editor::updateSaveMenu()
{
	char n = GetCharPressed();

	if (IsKeyPressed(KEY_BACKSPACE) && saveName.size() > 0)
	{
		saveName.pop_back();
	}
	else if (IsKeyPressed(KEY_ENTER))
	{
		saveMenu = false;
		std::ofstream save("./saves/" + saveName + ".txt");

		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				save << tiles[i][j] << " ";
			}
		}

		saveName.clear();
	}
	else if (n)
	{
		saveName.push_back(n);
	}

	closeSave.Clicked();
}

void Editor::updateLoadMenu()
{
	if (IsKeyPressed(KEY_DOWN))
	{
		if (currentSave < saves.size() - 1)
			currentSave++;
	}
	else if (IsKeyPressed(KEY_UP))
	{
		if (currentSave > 0)
			currentSave--;
	}
	else if (IsKeyPressed(KEY_ENTER))
	{
		loadMenu = false;

		if (saves.size())
		{
			std::ifstream load(saves[currentSave]);

			for (int i = 0; i < sizeY; i++)
			{
				for (int j = 0; j < sizeX; j++)
				{
					load >> tiles[i][j];
				}
			}
		}
	}
	else if (IsKeyPressed(KEY_DELETE))
	{
		std::remove(saves[currentSave].c_str());
		
		loadSaves();
		
		if(currentSave > 0)
			currentSave--;
	}
	
	closeLoad.Clicked();
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
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			updateRightClickPressed(mouse);
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

	if (tool == Tools::MULTI)
	{
		if (A.x == B.x)
		{
			len = B2.y - A2.y - 1;
			for (int i = A2.y + 1; i < B2.y; i++)
				tiles[i][(int)A2.x] = 1;
		}
		else if (A.y == B.y)
		{
			len = B2.x - A2.x - 1;
			for (int i = A2.x + 1; i < B2.x; i++)
				tiles[(int)A2.y][i] = 1;
		}
		else
		{
			len = B2.x - A.x - 1;
			len2 = B2.y - A2.y - 1;
			for (int i = A2.x + 1; i < B2.x; i++)
				for (int j = A2.y + 1; j < B2.y; j++)
					tiles[j][i] = 2;
		}

	}
	else if (tool == Tools::LINE)
	{
		if (A.x == B.x)
		{
			len = B2.y - A2.y - 1;
			for (int i = A2.y + 1; i < B2.y; i++)
				tiles[i][(int)A2.x] = 1;
		}
		else if (A.y == B.y)
		{
			len = B2.x - A2.x - 1;
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

	if (tool == Tools::MULTI)
	{
		if (A.x == B.x)
		{
			len = B2.y - A2.y - 1;
			for (int i = A2.y + 1; i < B2.y; i++)
				buffer[i][(int)A2.x] = 1;
		}
		else if (A.y == B.y)
		{
			len = B2.x - A2.x - 1;
			for (int i = A2.x + 1; i < B2.x; i++)
				buffer[(int)A2.y][i] = 1;
		}
		else
		{
			len = B2.x - A.x - 1;
			len2 = B2.y - A2.y - 1;
			for (int i = A2.x + 1; i < B2.x; i++)
				for (int j = A2.y + 1; j < B2.y; j++)
					buffer[j][i] = 2;
		}

	}
	else if (tool == Tools::LINE)
	{
		if (A.x == B.x)
		{
			len = B2.y - A2.y - 1;
			for (int i = A2.y + 1; i < B2.y; i++)
				buffer[i][(int)A2.x] = 1;
		}
		else if (A.y == B.y)
		{
			len = B2.x - A2.x - 1;
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

	case Tools::LINE:
		A = { (float)x, (float)y };
		break;

	case Tools::BUCKET:
		fillDFS(x, y, tiles[y][x], selected, tiles);
		break;

	case Tools::MULTI:
		tiles[y][x] = selected;
		A = { (float)x, (float)y };
		break;
	}
	model = createSingleModel(tiles);
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
		tool = Tools::PIXEL;
		break;
	case '2':
		tool = Tools::LINE;
		break;
	case '3':
		tool = Tools::BUCKET;
		break;
	case '4':
		tool = Tools::MULTI;
		break;
	}

	if (IsKeyPressed(KEY_ENTER))
	{
		calculateResources();
	}
}

void Editor::calculateResources()
{
	stoneTotal = 0;
	wallTotal = 0;
	slabTotal = 0;
	concreteTotal = 0;
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			if (tiles[i][j] == 0)
				stoneTotal += 4 * floors;
			else if (tiles[i][j] == 1)
			{
				stoneTotal += floors;
				if (tiles[i + 1][j] + 1 && tiles[i - 1][j] + 1 && tiles[i][j + 1] + 1 && tiles[i][j - 1] + 1)
					wallTotal += 3 * floors;
				else
					concreteTotal += 3 * floors;
			}
			if (tiles[i][j] == 2)
				slabTotal += floors;
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
	tools[0] = LoadTexture("textures/pixel.png");
	tools[1] = LoadTexture("textures/line.png");
	tools[2] = LoadTexture("textures/bucket.png");
	tools[3] = LoadTexture("textures/multitool.png");

	build[0] = LoadTexture("textures/pillar.png");
	build[1] = LoadTexture("textures/wall.png");
	build[2] = LoadTexture("textures/slab.png");

	auto temp1 = [&]() { tool = 0; };
	tools[0].setFunc(std::function<void()>(temp1));
	tools[0].setPos(GetScreenWidth() - 30, GetScreenHeight() / 2 - 45);
	auto temp2 = [&]() { tool = 1; };
	tools[1].setFunc(std::function<void()>(temp2));
	tools[1].setPos(GetScreenWidth() - 30, GetScreenHeight() / 2 - 15);
	auto temp3 = [&]() { tool = 2; };
	tools[2].setFunc(std::function<void()>(temp3));
	tools[2].setPos(GetScreenWidth() - 30, GetScreenHeight() / 2 + 15);
	auto temp4 = [&]() { tool = 3; };
	tools[3].setFunc(std::function<void()>(temp4));
	tools[3].setPos(GetScreenWidth() - 30, GetScreenHeight() / 2 + 45);

	auto temp5 = [&]() { selected = 0; };
	build[0].setFunc(std::function<void()>(temp5));
	build[0].setPos(GetScreenWidth() / 2 - 32, GetScreenHeight() - 32);
	auto temp6 = [&]() { selected = 1; };
	build[1].setFunc(std::function<void()>(temp6));
	build[1].setPos(GetScreenWidth() / 2, GetScreenHeight() - 32);
	auto temp7 = [&]() { selected = 2; };
	build[2].setFunc(std::function<void()>(temp7));
	build[2].setPos(GetScreenWidth() / 2 + 32, GetScreenHeight() - 32);

	auto temp8 = [&]() { saveMenu = false; };
	closeSave.setFunc(std::function<void()>(temp8));
	closeSave.setPos(GetScreenWidth() / 2 - 200, GetScreenHeight() / 2 - 32);
	closeSave.setColor({ 0, 0, 0, 200 });
	closeSave.setSize(20, 20);
	closeSave.setText("x");

	auto temp9 = [&]() { loadMenu = false; };
	closeLoad.setFunc(std::function<void()>(temp9));
	closeLoad.setPos(GetScreenWidth() / 2 - 200, 100);
	closeLoad.setColor({ 0, 0, 0, 200 });
	closeLoad.setSize(20, 20);
	closeLoad.setText("x");

	memset(tiles, -1, sizeof(tiles));
	memset(buffer, -1, sizeof(buffer));
}

void Editor::initCamera()
{
	view3D = LoadRenderTexture(GetScreenWidth() / 2 + 100, GetScreenHeight());

	cam.offset = { sizeX * tileSize * 0.25f, sizeY * tileSize * 0.25f };
	cam.rotation = 0;
	cam.target = { 0, 0 };
	cam.zoom = 1;

	cam3d.fovy = 45;
	cam3d.position = { 0.0f, 40, 0.0f };
	cam3d.projection = CAMERA_PERSPECTIVE;
	cam3d.target = { sizeX / 2, 10, sizeY / 2 };
	cam3d.up = { 0, 1, 0 };

	SetCameraMode(cam3d, CAMERA_FREE);
}

// Mesh Functions

void Editor::addCubeVertices(Vector3 * vertices, Color * colors, unsigned short* indices, int* vertexCount, int* indexCount, Vector3 pos, float width, float height, float depth, Color color)
{
	Vector3 cubeVertices[] = {
		{ pos.x, pos.y, pos.z },
		{ pos.x + width, pos.y, pos.z },
		{ pos.x, pos.y + height, pos.z },
		{ pos.x + width, pos.y + height, pos.z },
		{ pos.x, pos.y, pos.z + depth },
		{ pos.x + width, pos.y, pos.z + depth },
		{ pos.x, pos.y + height, pos.z + depth },
		{ pos.x + width, pos.y + height, pos.z + depth}
	};

	unsigned short cubeIndices[36] = {
		// Front face
		2, 1, 0, 2, 3, 1,
		// Right face
		7, 5, 1, 1, 3, 7,
		// Back face
		6, 4, 5, 5, 7, 6,
		// Left face
		2, 0, 4, 4, 6, 2,
		// Top face
		2, 6, 7, 7, 3, 2,
		// Bottom face
		5, 4, 0, 0, 1, 5
	};

	for (int i = 0; i < 8; i++)
	{
		vertices[*vertexCount] = cubeVertices[i];
		colors[*vertexCount] = color;
		(*vertexCount)++;
	}

	for (int i = 0; i < 36; i++)
	{
		indices[*indexCount] = cubeIndices[i] + (*vertexCount) - 8;
		(*indexCount)++;
	}
}

Model Editor::createSingleModel(char tiles[sizeY][sizeX], Vector3 pos)
{
	int maxVertices = sizeX * sizeY * floors * 8;
	int maxIndices = sizeX * sizeY * floors * 36;

	int visited[sizeY][sizeX] = { 0 };

	Vector3* vertices = (Vector3*)malloc(maxVertices * sizeof(Vector3));
	Color* colors = (Color*)malloc(maxVertices * sizeof(Color));
	unsigned short* indices = (unsigned short*)malloc(maxIndices * sizeof(unsigned short));

	int vertexCount = 0;
	int indexCount = 0;

	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			char type = tiles[i][j];
			Color color;
			float height;
			Vector3 pos;

			switch (type)
			{
			case 0:
				color = RED;
				height = 4.0f * (floors - 1) + 1.0f;
				pos = { (float)j, 0, (float)i };

				addCubeVertices(vertices, colors, indices, &vertexCount, &indexCount, pos, 1.0f, height, 1.0f, color);
				continue;
			case 1:
				color = GREEN;
				height = 1.0f;
				break;
			case 2:
				color = BLUE;
				height = 0.5f;
				break;
			default:
				continue;
			}

			int width = 0, length = 0;

			if (tiles[i][j] > 0 && visited[i][j] == 0)
			{
				int value = tiles[i][j];

				for (int col = j; col < sizeX && tiles[i][col] == value && visited[i][col] == 0; col++)
					width++;

				for (int row = i; row < sizeY && tiles[row][j] == value && visited[row][j] == 0; row++)
					length++;

				for (int x = i; x < i + length; x++)
					for (int y = j; y < j + width; y++)
						if(tiles[x][y] == value)
							visited[x][y] = 1;

				for (int k = 0; k < floors; k++)
				{
					float yPos = k * 4.0f;
					if (type == 0 && k == floors - 1)
					{
						height = 1.0f;
					}

					pos = { (float)j, yPos, (float)i };

					addCubeVertices(vertices, colors, indices, &vertexCount, &indexCount, pos, width, height, length, color);
				}
			}
		}
	}

	Model model = LoadModelFromMesh({ 0 });

	model.meshCount = (vertexCount + 65520 - 1) / 65520;

	Vector3** splitVertices = (Vector3**)malloc(model.meshCount * sizeof(Vector3*));
	Color** splitColors = (Color**)malloc(model.meshCount * sizeof(Color*));
	unsigned short** splitIndices = (unsigned short**)malloc(model.meshCount * sizeof(unsigned short*));
	int* vertexCounts = (int*)malloc(model.meshCount * sizeof(int));
	int* indexCounts = (int*)malloc(model.meshCount * sizeof(int));

	int vertexOffset = 0, indexOffset = 0;

	for (int i = 0; i < model.meshCount; i++)
	{
		int currentVertexCount = (i == model.meshCount - 1) ? (vertexCount % 65520) : 65520;

		if (currentVertexCount == 0 && i == model.meshCount - 1)
			currentVertexCount = 65520;

		int currentIndexCount = 4.5 * currentVertexCount;

		splitVertices[i] = vertices + vertexOffset;
		splitIndices[i] = indices + indexOffset;
		splitColors[i] = colors + vertexOffset;

		vertexCounts[i] = currentVertexCount;
		indexCounts[i] = currentIndexCount;

		vertexOffset += currentVertexCount + model.meshCount * 8;
		indexOffset += currentIndexCount + model.meshCount * 36;
	}

	Mesh* meshes = (Mesh*)malloc(model.meshCount * sizeof(Mesh));

	for (int i = 0; i < model.meshCount; i++)
	{
		Mesh mesh = { 0 };
		mesh.vertexCount = vertexCounts[i];
		mesh.triangleCount = indexCounts[i] / 3;

		mesh.vertices = (float*)splitVertices[i];

		mesh.indices = splitIndices[i];
		mesh.colors = (unsigned char*)splitColors[i];

		UploadMesh(&mesh, true);

		meshes[i] = mesh;
	}

	model.meshes = meshes;

	model.materialCount = 1;

	UpdateTransform(model, { 0, 0, 0 });
	free(vertices);
	free(splitVertices);
	free(vertexCounts);

	free(indices);
	free(splitIndices);
	free(indexCounts);

	free(colors);
	free(splitColors);

	return model;
}