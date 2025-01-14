#pragma once
#include "raylib.h"
#include "scene.h"
#include "globals.h"
#include "utils.h"

#include <fstream>
#include <vector>
#include <filesystem>
#include <string>

class Planner : public Scene
{
public:
	Planner();

	void Update() override;
	void Draw() override;
	void BackgroundUpdates() override;
	void OnSwitch() override;

private:
	void loadModels();
	void initCamera();

	// Update functions
	void onWindowResize();

	// Draw functions

	Camera cam3d;
	Camera2D cam;

	std::vector<Model> blocs;
};
