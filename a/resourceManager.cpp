#include "resourceManager.h"

ResourceManager* ResourceManager::GetInstance()
{
	if (resources == nullptr)
		resources = new ResourceManager();

	return ResourceManager::resources;
}

uint32_t ResourceManager::AddTexture(std::string path)
{
	textures[textureIds] = LoadTexture(path.c_str());
	textureIds++;
	return textureIds - 1;
}

uint32_t ResourceManager::LoadModel(Model& model)
{
	models[modelIds] = model;
	modelIds++;
	return modelIds - 1;
}

Texture2D* ResourceManager::GetTexture(uint32_t id)
{
	if(textureIds < id)
		return &textures[id];
	return nullptr;
}

Model* ResourceManager::GetModel(uint32_t id)
{
	if (modelIds < id)
		return &models[id];
	return nullptr;
}