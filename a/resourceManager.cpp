#include "resourceManager.h"

ResourceManager* ResourceManager::_resources = nullptr;

ResourceManager* ResourceManager::GetInstance()
{
	if (_resources == nullptr)
		_resources = new ResourceManager();

	return ResourceManager::_resources;
}

// Setters

uint32_t ResourceManager::ResLoadTexture(std::string path)
{
	textures[textureIds] = LoadTexture(path.c_str());
	textureIds++;
	std::cout << textureIds << std::endl;
	return textureIds - 1;
}

uint32_t ResourceManager::AddTexture(Texture2D& texture)
{
	textures[textureIds] = texture;
	textureIds++;
	return textureIds - 1;
}

uint32_t ResourceManager::AddRenderTexture(RenderTexture& renderTexture)
{
	renderTextures[renderTextureIds] = renderTexture;
	renderTextureIds++;
	return renderTextureIds - 1;
}

uint32_t ResourceManager::AddModel(Model& model)
{
	models[modelIds] = model;
	modelIds++;
	return modelIds - 1;
}

// Getters

Texture2D ResourceManager::GetTexture(uint32_t id)
{
	if(id < textureIds)
		return textures[id];
	return { 0 };
}

RenderTexture ResourceManager::GetRenderTexture(uint32_t id)
{
	if (id < renderTextureIds)
		return renderTextures[id];
	return { 0 };
}

Model ResourceManager::GetModel(uint32_t id)
{
	if (id < modelIds)
		return models[id];
	return { 0 };
}