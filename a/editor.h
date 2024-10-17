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

struct BlocData
{
	int stoneTotal = 0;
	int slabTotal = 0;
	int wallTotal = 0;
	int floors = 1;
	int concreteTotal = 0;
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
	void updateTiles();

	void updateLeftClickPressed(Vector2& mouse);
	void updateLeftClickDown(Vector2& mouse);
	void updateLeftClickRelease();
	void updateRightClickPressed(Vector2& mouse);

	void updateTools();

	void calculateResources();
	void loadSaves();

	BlocData data;

	// Tools related
	Vector2 A, B;

	char tool = Tools::TMULTI;
	int len, len2;

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

	Shader* shader;
	Material* bloc;
	RenderTexture* render;

	Camera2D cam;
	Camera cam3d;

	ResourceManager* resources;
};