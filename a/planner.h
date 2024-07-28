#pragma once
#include "raylib.h"
#include "scene.h"

class Planner : public Scene
{
public:
	Planner();

	void Update() override;
	void Draw() override;
	void BackgroundUpdates() override;

private:
	void onWindowResize();

	Camera cam3d;
	Camera2D cam;

	double rot;
};