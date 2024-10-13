#pragma once

#include "resourceManager.h"

const int tileSize = 16;
const int sizeX = 40;
const int sizeY = 40;

enum Textures
{
	PIXEL,
	LINE,
	BUCKET,
	MULTITOOL,
	PILLAR,
	WALL,
	SLAB
};

inline void LoadTextures()
{
	ResourceManager* resources = ResourceManager::GetInstance();

	resources->ResLoadTexture("textures/pixel.png");
	resources->ResLoadTexture("textures/line.png");
	resources->ResLoadTexture("textures/bucket.png");
	resources->ResLoadTexture("textures/multitool.png");

	resources->ResLoadTexture("textures/pillar.png");
	resources->ResLoadTexture("textures/wall.png");
	resources->ResLoadTexture("textures/slab.png");
}