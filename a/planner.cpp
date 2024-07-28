#include "planner.h"

Planner::Planner()
{
	cam.offset = { GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f};
	cam.rotation = 0;
	cam.target = { 0, 0 };
	cam.zoom = 1;
}

void Planner::Update()
{
	rot += GetFrameTime() * 10;
	cam.rotation = rot;
}

void Planner::Draw()
{
	BeginMode2D(cam);
	DrawText("planer", 100, 100, 50, BLACK);
	EndMode2D();
}

void Planner::BackgroundUpdates()
{
	if (IsWindowResized())
		onWindowResize();
}

void Planner::onWindowResize()
{
	cam.offset = { GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f };
}