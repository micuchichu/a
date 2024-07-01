#include <iostream>
#include <string>
#include <fstream>

#include "raylib.h"
#include "gui.h"

const int tileSize = 16;
const int sizeX = 40;
const int sizeY = 40;

int stoneTotal = 0;
int slabTotal = 0;
int wallTotal = 0;
int etaje = 1;
int concreteTotal = 0;

char tiles[sizeY][sizeX];
char buffer[sizeY][sizeX];

Vector2 A, B;

enum Tools
{
	PIXEL,
	LINE,
	BUCKET,
	MULTI,
};

void drawTotals(int x, int y)
{
	DrawText(TextFormat("Stone: %d", stoneTotal), x + 10, y + 10, 30, GRAY);
	DrawText(TextFormat("Slabs: %d", slabTotal), x + 10, y + 40, 30, GRAY);
	DrawText(TextFormat("Walls: %d", wallTotal), x + 10, y + 70, 30, GRAY);
	DrawText(TextFormat("Concrete: %d", concreteTotal), x + 10, y + 100, 30, GRAY);
	DrawText(TextFormat("Etaje: %d", etaje), x + 10, y + 130, 30, GRAY);
	DrawText(TextFormat("Total Stone: %d", stoneTotal + slabTotal / 2 + wallTotal), x + 190, y + 10, 30, GRAY);
}

void drawCube(char type, int x, int y)
{
	Vector3 pos;
	switch (type)
	{
	case 0:
		for (int i = 0; i < etaje - 1; i++)
		{
			pos = { (float)x, i * 4.0f + 1.5f, (float)y };
			DrawCube(pos, 1.0f, 4, 1.0f, RED);
			DrawCubeWires(pos, 1.0f, 4, 1.0f, BLACK);
		}
		pos = { (float)x, (etaje - 1) * 4.0f, (float)y };
		DrawCube(pos, 1.0f, 1.0f, 1.0f, RED);
		DrawCubeWires(pos, 1.0f, 1.0f, 1.0f, BLACK);
		return;
	case 1:
		for (int i = 0; i < etaje; i++)
		{
			pos = { (float)x, i * 4.0f, (float)y};
			DrawCube(pos, 1.0f, 1.0f, 1.0f, GREEN);
			DrawCubeWires(pos, 1.0f, 1.0f, 1.0f, BLACK);
		}
		return;
	case 2:
		for (int i = 0; i < etaje; i++)
		{
			pos = { (float)x, i * 4.0f, (float)y};
			DrawCube(pos, 1.0f, 0.5f, 1.0f, BLUE);
			DrawCubeWires(pos, 1.0f, 0.5f, 1.0f, BLACK);
		}
		return;
	}
}

void drawTile(char type, int x, int y)
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

void fillDFS(int x, int y, char oldColor, char newColor) 
{
	if (x < 0 || x >= sizeX || y < 0 || y >= sizeY || tiles[x][y] != oldColor || tiles[x][y] == newColor)
		return;

	tiles[x][y] = newColor;

	fillDFS(x + 1, y, oldColor, newColor);
	fillDFS(x - 1, y, oldColor, newColor);
	fillDFS(x, y + 1, oldColor, newColor);
	fillDFS(x, y - 1, oldColor, newColor);
}

int main()
{
	int len = 0, len2 = 0;

	Camera2D cam;
	cam.offset = { sizeX * tileSize * 0.25f, sizeY * tileSize * 0.25f };
	cam.rotation = 0;
	cam.target = { 0, 0 };
	cam.zoom = 1;

	Camera cam3d;
	cam3d.fovy = 45;
	cam3d.position = { 0.0f, 40, 0.0f };
	cam3d.projection = CAMERA_PERSPECTIVE;
	cam3d.target = { sizeX / 2, 10, sizeY / 2 };
	cam3d.up = { 0, 1, 0 };

	SetCameraMode(cam3d, CAMERA_ORBITAL);

	Vector2 mouse;

	char tool = Tools::MULTI;

	SetWindowState(FLAG_WINDOW_RESIZABLE);

	InitWindow(800, 600, "caca");

	SetTargetFPS(40);

	char selected = 0;

	Button tools[4];
	Button build[3];

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

	for (int i = 0; i < sizeX; i++)
		for (int j = 0; j < sizeY; j++)
		{
			tiles[i][j] = -1;
			buffer[i][j] = -1;
		}

	RenderTexture2D renderTexture = LoadRenderTexture(GetScreenWidth() / 2 + 100, GetScreenHeight());

	while(!WindowShouldClose())
	{
		len = 0;
		len2 = 0;
		mouse = GetScreenToWorld2D(GetMousePosition(), cam);
		UpdateCamera(&cam3d);

		if (IsWindowResized())
		{
			tools[0].setPos(GetScreenWidth() - 30, GetScreenHeight() / 2 - 45);
			tools[1].setPos(GetScreenWidth() - 30, GetScreenHeight() / 2 - 15);
			tools[2].setPos(GetScreenWidth() - 30, GetScreenHeight() / 2 + 15);
			tools[3].setPos(GetScreenWidth() - 30, GetScreenHeight() / 2 + 45);

			build[0].setPos(GetScreenWidth() / 2 - 32, GetScreenHeight() - 32);
			build[1].setPos(GetScreenWidth() / 2, GetScreenHeight() - 32);
			build[2].setPos(GetScreenWidth() / 2 + 32, GetScreenHeight() - 32);

			renderTexture = LoadRenderTexture(GetScreenWidth() / 2 + 100, GetScreenHeight());
		}

		if (mouse.x > 0 && mouse.y > 0 && mouse.x < sizeX * tileSize && mouse.y < sizeY * tileSize)
		{

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				int x, y;
				switch (tool)
				{
				case PIXEL:
					y = (int)(mouse.x / tileSize);
					x = (int)(mouse.y / tileSize);
					tiles[y][x] = selected;
					break;

				case Tools::LINE:
					y = (int)(mouse.x / tileSize);
					x = (int)(mouse.y / tileSize);
					A = { (float)x, (float)y };
					break;

				case Tools::BUCKET:
					y = (int)(mouse.x / tileSize);
					x = (int)(mouse.y / tileSize);
					fillDFS(x, y, tiles[y][x], selected);
					break;

				case Tools::MULTI:
					y = (int)(mouse.x / tileSize);
					x = (int)(mouse.y / tileSize);
					tiles[y][x] = selected;
					A = { (float)x, (float)y };
					break;
				}
			}

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				memset(buffer, -1, sizeof(buffer));
				int y = mouse.x / tileSize;
				int x = mouse.y / tileSize;
				B = { (float)x, (float)y };
				if (tool == Tools::MULTI)
				{

					if (A.x == B.x)
					{
						len = std::abs(A.y - B.y) - 1;
						if (A.y < B.y)
							for (int i = A.y + 1; i < B.y; i++)
								buffer[i][(int)A.x] = 1;
						else
							for (int i = B.y + 1; i < A.y; i++)
								buffer[i][(int)A.x] = 1;
					}
					else if (A.y == B.y)
					{
						len = std::abs(A.x - B.x) - 1;
						if (A.x < B.x)
							for (int i = A.x + 1; i < B.x; i++)
								buffer[(int)A.y][i] = 1;
						else
							for (int i = B.x + 1; i < A.x; i++)
								buffer[(int)A.y][i] = 1;
					}
					else
					{
						len = std::abs(A.x - B.x) - 1;
						len2 = std::abs(A.y - B.y) - 1;
						if (A.x < B.x && A.y < B.y)
							for (int i = A.x + 1; i < B.x; i++)
								for (int j = A.y + 1; j < B.y; j++)
									buffer[j][i] = 2;
						else if (A.x > B.x && A.y < B.y)
							for (int i = B.x + 1; i < A.x; i++)
								for (int j = A.y + 1; j < B.y; j++)
									buffer[j][i] = 2;
						else if (A.x < B.x && A.y > B.y)
							for (int i = A.x + 1; i < B.x; i++)
								for (int j = B.y + 1; j < A.y; j++)
									buffer[j][i] = 2;
						else if (A.x > B.x && A.y > B.y)
							for (int i = B.x + 1; i < A.x; i++)
								for (int j = B.y + 1; j < A.y; j++)
									buffer[j][i] = 2;
					}

				}
				else if (tool == Tools::LINE)
				{
					if (A.x == B.x)
					{
						len = std::abs(A.y - B.y) - 1;
						if (A.y < B.y)
							for (int i = A.y + 1; i < B.y; i++)
								buffer[i][(int)A.x] = 1;
						else
							for (int i = B.y + 1; i < A.y; i++)
								buffer[i][(int)A.x] = 1;
					}
					else if (A.y == B.y)
					{
						len = std::abs(A.x - B.x) - 1;
						if (A.x < B.x)
							for (int i = A.x + 1; i < B.x; i++)
								buffer[(int)A.y][i] = 1;
						else
							for (int i = B.x + 1; i < A.x; i++)
								buffer[(int)A.y][i] = 1;
					}
				}
			}

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				memset(buffer, -1, sizeof(buffer));

				if (tool == Tools::MULTI)
				{
					if (A.x == B.x)
					{
						if (A.y < B.y)
							for (int i = A.y + 1; i < B.y; i++)
								tiles[i][(int)A.x] = 1;
						else
							for (int i = B.y + 1; i < A.y; i++)
								tiles[i][(int)A.x] = 1;
					}
					else if (A.y == B.y)
					{
						if (A.x < B.x)
							for (int i = A.x + 1; i < B.x; i++)
								tiles[(int)A.y][i] = 1;
						else
							for (int i = B.x + 1; i < A.x; i++)
								tiles[(int)A.y][i] = 1;
					}
					else
					{
						if (A.x < B.x && A.y < B.y)
							for (int i = A.x + 1; i < B.x; i++)
								for (int j = A.y + 1; j < B.y; j++)
									tiles[j][i] = 2;
						else if (A.x > B.x && A.y < B.y)
							for (int i = B.x + 1; i < A.x; i++)
								for (int j = A.y + 1; j < B.y; j++)
									tiles[j][i] = 2;
						else if (A.x < B.x && A.y > B.y)
							for (int i = A.x + 1; i < B.x; i++)
								for (int j = B.y + 1; j < A.y; j++)
									tiles[j][i] = 2;
						else if (A.x > B.x && A.y > B.y)
							for (int i = B.x + 1; i < A.x; i++)
								for (int j = B.y + 1; j < A.y; j++)
									tiles[j][i] = 2;
					}
				}
				else if (tool == Tools::LINE)
				{
					if (A.x == B.x)
					{
						if (A.y < B.y)
							for (int i = A.y + 1; i < B.y; i++)
								tiles[i][(int)A.x] = 1;
						else
							for (int i = B.y + 1; i < A.y; i++)
								tiles[i][(int)A.x] = 1;
					}
					else if (A.y == B.y)
					{
						if (A.x < B.x)
							for (int i = A.x + 1; i < B.x; i++)
								tiles[(int)A.y][i] = 1;
						else
							for (int i = B.x + 1; i < A.x; i++)
								tiles[(int)A.y][i] = 1;
					}
				}
			}

			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), cam);
				int y = (int)(mouse.x / tileSize);
				int x = (int)(mouse.y / tileSize);
				tiles[y][x] = -1;
			}
		}

		for (int i = 0; i < 4; i++)
			tools[i].Clicked();

		for (int i = 0; i < 3; i++)
			build[i].Clicked();

		if (IsKeyPressed('S'))
		{
			std::ofstream save("saves/save.txt");

			for (int i = 0; i < sizeY; i++)
			{
				for (int j = 0; j < sizeX; j++)
				{
					save << tiles[i][j] << " ";
				}
			}
		}

		if (IsKeyPressed('L'))
		{
			std::ifstream load("saves/save.txt");

			for (int i = 0; i < sizeY; i++)
			{
				for (int j = 0; j < sizeX; j++)
				{
					load >> tiles[i][j];
				}
			}
		}

		if (IsKeyPressed('R'))
		{
			for (int i = 0; i < sizeY; i++)
			{
				for(int j = 0; j < sizeX; j++)
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

		etaje += IsKeyPressed(KEY_UP);
		etaje -= IsKeyPressed(KEY_DOWN);

		if (IsKeyPressed(KEY_ENTER))
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
						stoneTotal += 4 * etaje;
					else if (tiles[i][j] == 1)
					{
						stoneTotal += etaje;
						if (tiles[i + 1][j] + 1 && tiles[i - 1][j] + 1 && tiles[i][j + 1] + 1 && tiles[i][j - 1] + 1)
							wallTotal += 3 * etaje;
						else
							concreteTotal += 3 * etaje;
					}
					if (tiles[i][j] == 2)
						slabTotal += etaje;
				}
			}
		}

		BeginTextureMode(renderTexture);
		ClearBackground(WHITE);

		BeginMode3D(cam3d);
		
		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				drawCube(tiles[i][j], i, j);
			}
		}

		EndMode3D();

		EndTextureMode();


		BeginDrawing();
		ClearBackground(WHITE);

		DrawTexturePro(renderTexture.texture, { 0, 0, (float)renderTexture.texture.width, -(float)renderTexture.texture.height }, { GetScreenWidth() * 0.5f - 100, 0, (float)renderTexture.texture.width, (float)renderTexture.texture.height}, {0, 0}, 0, WHITE);
		
		BeginMode2D(cam);

		for (int i = 0; i < sizeY; i++)
			for (int j = 0; j < sizeX; j++)
			{
				drawTile(tiles[i][j], i * tileSize, j * tileSize);
				drawTile(buffer[i][j], i * tileSize, j * tileSize);
			}

		EndMode2D();
		if (len)
			DrawText(TextFormat("%d", len), GetMouseX() + 25, GetMouseY(), 20, BLACK);
		if (len2)
			DrawText(TextFormat("%d", len2), GetMouseX(), GetMouseY() + 25, 20, BLACK);

		for (int i = 0; i < 4; i++)
			tools[i].DrawButton();

		for (int i = 0; i < 3; i++)
			build[i].DrawButton(0.2f);

		drawTotals(0, 0);

		DrawText(TextFormat("Tool: %d", tool), 10, GetScreenHeight() - 30, 30, GRAY);

		EndDrawing();
	}
	CloseWindow();
}
