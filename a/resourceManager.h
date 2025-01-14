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
	uint32_t ResLoadRenderTexture(int width, int height);
	uint32_t ResLoadModel(std::string path);
	uint32_t ResLoadShader(std::string vspath, std::string fspath);
	uint32_t ResLoadMaterial();

	void ReloadTexture(uint32_t id, std::string path);
	void ReloadRenderTexture(uint32_t id, int width, int height);
	void ReloadModel(uint32_t id, std::string path);
	void ReloadShader(uint32_t id, std::string vspath, std::string fspath);
	void ReloadMaterial(uint32_t id);

	uint32_t AddTexture(Texture2D& texture);
	uint32_t AddRenderTexture(RenderTexture& renderTexture);
	uint32_t AddModel(Model& model);
	uint32_t AddShader(Shader& shader);
	uint32_t AddMaterial(Material& material);

	Texture2D* GetTexture(uint32_t id);
	RenderTexture* GetRenderTexture(uint32_t id);
	Model* GetModel(uint32_t id);
	Shader* GetShader(uint32_t id);
	Material* GetMaterial(uint32_t id);

	void UnloadTextures();
	void UnloadRenderTextures();
	void UnloadModels();
	void UnloadShaders();
	void UnloadMaterials();

	void MaterialAddTexture(uint32_t materialId, uint32_t textureId);
	void MaterialAddShader(uint32_t materialId, uint32_t shaderId);

private:
	ResourceManager() = default;

	static ResourceManager* _resources;

	uint32_t textureIds;
	uint32_t renderTextureIds;
	uint32_t modelIds;
	uint32_t shaderIds;
	uint32_t materialIds;

	std::unordered_map<uint32_t, Texture2D> textures;
	std::unordered_map<uint32_t, RenderTexture> renderTextures;
	std::unordered_map<uint32_t, Model> models;
	std::unordered_map<uint32_t, Shader> shaders;
	std::unordered_map<uint32_t, Material> materials;
};