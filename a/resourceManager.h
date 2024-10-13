#pragma once

#include "raylib.h"

#include <iostream>
#include <unordered_map>

class ResourceManager
{
public:
	ResourceManager(ResourceManager& other) = delete;

	void operator = (const ResourceManager other) = delete;

	ResourceManager* GetInstance();

	static ResourceManager* resources;

	uint32_t AddTexture(std::string path);
	uint32_t LoadModel(Model& model);

	Texture2D* GetTexture(uint32_t id);
	Model* GetModel(uint32_t id);

private:
	ResourceManager() = default;

	uint32_t textureIds;
	uint32_t modelIds;

	std::unordered_map<uint32_t, Texture2D> textures;
	std::unordered_map<uint32_t, Model> models;
};

ResourceManager *ResourceManager::resources = nullptr;

