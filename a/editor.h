#pragma once

#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

#include "resourceManager.h"
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
	TPIXEL,
	TLINE,
	TFILL,
	TMULTI,
};

class Editor : public Scene
{
public:
	Editor();

	// Main functions
	void Draw() override;
	void Update() override;
	void BackgroundUpdates() override;
	void OnSwitch() override;

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
	void drawModel();

	// Update functions
	void onWindowResize();

	void updateModel();
	//void updateSaveMenu();
	//void updateLoadMenu();

	void updateTiles();

	void updateLeftClickPressed(Vector2& mouse);
	void updateLeftClickDown(Vector2& mouse);
	void updateLeftClickRelease();
	void updateRightClickPressed(Vector2& mouse);

	void updateTools();

	void calculateResources();
	void loadSaves();

	// Data
	int stoneTotal = 0;
	int slabTotal = 0;
	int wallTotal = 0;
	int floors = 1;
	int concreteTotal = 0;

	// Tools related
	Vector2 A, B;

	char tool = Tools::TMULTI;
	int len, len2;

	std::vector<int> textures;

	// save/load related
	std::vector<std::string> saves;
	char buf[32];

	int currentSave = 0;

	bool saveMenu = false;
	bool loadMenu = false;

	// Misc
	char selected = 0;
	double angle = 0;

	// Render
	char tiles[sizeY][sizeX];
	char buffer[sizeY][sizeX];

	float time;

	Model model = { 0 };

	RenderTexture2D view3D;

	ResourceManager* resources;

	Shader shader;

	Camera2D cam;
	Camera cam3d;

	Material bloc;
};