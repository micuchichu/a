#include "scene.h"

void Scene::Draw()
{
	DrawText("Scene is empty", GetScreenWidth() / 2, GetScreenHeight() / 2, 20, BLACK);
}

void Scene::Update()
{
	std::cout << "EMPTY" << std::endl;
}