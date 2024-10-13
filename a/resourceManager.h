#pragma once

#include "raylib.h"

#include <unordered_map>
#include <string>
#include <iostream>

class ResourceManager
{
public:
	ResourceManager(ResourceManager& other) = delete;

	void operator = (const ResourceManager other) = delete;

	static ResourceManager* GetInstance();

	uint32_t ResLoadTexture(std::string path);
	uint32_t AddTexture(Texture2D& texture);
	uint32_t AddRenderTexture(RenderTexture& renderTexture);
	uint32_t AddModel(Model& model);

	Texture2D GetTexture(uint32_t id);
	RenderTexture GetRenderTexture(uint32_t id);
	Model GetModel(uint32_t id);

private:
	ResourceManager() = default;

	static ResourceManager* _resources;

	uint32_t textureIds;
	uint32_t modelIds;
	uint32_t renderTextureIds;

	std::unordered_map<uint32_t, Texture2D> textures;
	std::unordered_map<uint32_t, Model> models;
	std::unordered_map<uint32_t, RenderTexture> renderTextures;
};

//ResourceManager* ResourceManager::_resources = nullptr;

