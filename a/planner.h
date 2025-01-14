#pragma once
#include "raylib.h"
#include "scene.h"
#include "globals.h"
#include "utils.h"

#include <fstream>
#include <vector>
#include <filesystem>
#include <string>

struct blocData
{
	Model model;
	RenderTexture info;
	int floors;

	int stoneTotal = 0;
	int slabTotal = 0;
	int wallTotal = 0;
	int concreteTotal = 0;
};

class Planner : public Scene
{
public:
	Planner();

	void Update() override;
	void Draw() override;
	void BackgroundUpdates() override;
	void OnSwitch() override;

private:
	// Update functions
	void onWindowResize();

	// Draw functions
	void drawTools();
	void drawBlocs();
	void drawInfo();

	void loadModels();
	void initCamera();

	bool cameraActive;

	Camera cam3d;
	Camera2D cam;

	std::vector<blocData> blocs;
	std::vector<std::string> saves;
};
