#pragma once

#include "raylib.h"
#include "utils.h"
#include "globals.h"
#include "gui.h"
#include "scene.h"


#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

enum Tools
{
	PIXEL,
	LINE,
	BUCKET,
	MULTI,
};

class Editor : public Scene
{
public:
	Editor();

	// Main functions
	void Draw() override;
	void Update() override;
	void BackgroundUpdates() override;

private:
	// Load functions
	void initTools();
	void initCamera();

	// Draw functions
	void drawTotals(int x, int y);
	void drawTile(char type, int x, int y);
	void drawSaveMenu();
	void drawLoadMenu();
	void drawTiles();

	// Update functions
	void onWindowResize();

	void updateModel();
	void updateSaveMenu();
	void updateLoadMenu();

	void updateTiles();

	void updateLeftClickPressed(Vector2& mouse);
	void updateLeftClickDown(Vector2& mouse);
	void updateLeftClickRelease();
	void updateRightClickPressed(Vector2& mouse);

	void updateTools();

	void calculateResources();
	void loadSaves();

	// Mesh related functions
	void addCubeVertices(Vector3* vertices, Color* colors, unsigned short* indices, int* vertexCount, int* indexCount, Vector3 pos, float width, float height, float depth, Color color);
	Model createSingleModel(char tiles[sizeY][sizeX], Vector3 pos = { 0 });

	// Data
	int stoneTotal = 0;
	int slabTotal = 0;
	int wallTotal = 0;
	int floors = 1;
	int concreteTotal = 0;

	// Tools related
	Vector2 A, B;

	char tool = Tools::MULTI;
	Button tools[4];
	Button build[3];
	int len, len2;

	// save/load related
	std::vector<std::string> saves;
	std::string saveName;
	Button closeSave;
	Button closeLoad;

	int currentSave = 0;

	bool saveMenu = false;
	bool loadMenu = false;

	// Misc
	char selected = 0;
	double angle = 0;

	// Render
	char tiles[sizeY][sizeX];
	char buffer[sizeY][sizeX];

	Model model = { 0 };

	RenderTexture2D view3D;

	Camera2D cam;
	Camera cam3d;
};