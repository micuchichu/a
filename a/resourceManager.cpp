#include "resourceManager.h"

ResourceManager* ResourceManager::_resources = nullptr;

ResourceManager* ResourceManager::GetInstance()
{
	if (_resources == nullptr)
		_resources = new ResourceManager();

	return ResourceManager::_resources;
}

// Loaders

uint32_t ResourceManager::ResLoadTexture(std::string path)
{
	textures[textureIds] = LoadTexture(path.c_str());
	textureIds++;
	return textureIds - 1;
}

uint32_t ResourceManager::ResLoadRenderTexture(int width, int height)
{
	renderTextures[renderTextureIds] = LoadRenderTexture(width, height);
	renderTextureIds++;
	return renderTextureIds - 1;
}

uint32_t ResourceManager::ResLoadModel(std::string path)
{
	models[modelIds] = LoadModel(path.c_str());
	modelIds++;
	return modelIds - 1;
}

uint32_t ResourceManager::ResLoadShader(std::string vspath, std::string fspath)
{
	shaders[shaderIds] = LoadShader(vspath.c_str(), fspath.c_str());
	shaderIds++;
	return shaderIds - 1;
}

uint32_t ResourceManager::ResLoadMaterial()
{
	materials[materialIds] = LoadMaterialDefault();
	materialIds++;
	return materialIds - 1;
}

// Reloaders

void ResourceManager::ReloadTexture(uint32_t id, std::string path)
{
	if (id < textureIds)
		textures[id] = LoadTexture(path.c_str());
}

void ResourceManager::ReloadRenderTexture(uint32_t id, int width, int height)
{
	if (id < renderTextureIds)
		renderTextures[id] = LoadRenderTexture(width, height);
}

void ResourceManager::ReloadModel(uint32_t id, std::string path)
{
	if (id < modelIds)
		models[id] = LoadModel(path.c_str());
}

void ResourceManager::ReloadShader(uint32_t id, std::string vspath, std::string fspath)
{
	if (id < shaderIds)
		shaders[id] = LoadShader(vspath.c_str(), fspath.c_str());
}

void ResourceManager::ReloadMaterial(uint32_t id)
{
	if (id < materialIds)
		materials[id] = LoadMaterialDefault();
}

// Unloaders

void ResourceManager::UnloadTextures()
{
	for (uint32_t i = 0; i < textureIds; i++)
		UnloadTexture(textures[i]);
}

void ResourceManager::UnloadRenderTextures()
{
	for (uint32_t i = 0; i < renderTextureIds; i++)
		UnloadRenderTexture(renderTextures[i]);
}

void ResourceManager::UnloadModels()
{
	for (uint32_t i = 0; i < modelIds; i++)
		UnloadModel(models[i]);
}

void ResourceManager::UnloadShaders()
{
	for (uint32_t i = 0; i < shaderIds; i++)
		UnloadShader(shaders[i]);
}

void ResourceManager::UnloadMaterials()
{
	for (uint32_t i = 0; i < materialIds; i++)
		UnloadMaterial(materials[i]);
}

// Setters

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

uint32_t ResourceManager::AddShader(Shader& shader)
{
	shaders[shaderIds] = shader;
	shaderIds++;
	return shaderIds - 1;
}

uint32_t ResourceManager::AddMaterial(Material& material)
{
	materials[materialIds] = material;
	materialIds++;
	return materialIds - 1;
}


void ResourceManager::MaterialAddShader(uint32_t materialId, uint32_t shaderId)
{
	if (materialId < materialIds && shaderId < shaderIds)
		materials[materialId].shader = shaders[shaderId];
}

void ResourceManager::MaterialAddTexture(uint32_t materialId, uint32_t textureId)
{
	if (materialId < materialIds && textureId < textureIds)
		materials[materialId].maps[MATERIAL_MAP_DIFFUSE].texture = textures[textureId];
}

// Getters

Texture2D* ResourceManager::GetTexture(uint32_t id)
{
	if(id < textureIds)
		return &textures[id];
	return { 0 };
}

RenderTexture* ResourceManager::GetRenderTexture(uint32_t id)
{
	if (id < renderTextureIds)
		return &renderTextures[id];
	return { 0 };
}

Model* ResourceManager::GetModel(uint32_t id)
{
	if (id < modelIds)
		return &models[id];
	return { 0 };
}

Shader* ResourceManager::GetShader(uint32_t id)
{
	if (id < shaderIds)
		return &shaders[id];
	return { 0 };
}

Material* ResourceManager::GetMaterial(uint32_t id)
{
	if (id < materialIds)
		return &materials[id];
	return { 0 };
}