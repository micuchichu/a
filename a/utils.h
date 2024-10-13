#pragma once

#include "raylib.h"
#include "raymath.h"
#include "globals.h"
#include "imgui.h"

#include <iostream>
#include <cmath>

void ImGuiStyleSetup();

void fillDFS(int x, int y, char oldColor, char newColor, char tiles[sizeX][sizeY]);

void UpdateTransform(Model& model, Vector3 newPos);

void addCubeVertices(Vector3* vertices, Color* colors, unsigned short* indices, int* vertexCount, int* indexCount, Vector2* texcoords, Vector3* normals, Vector3 pos, float width, float height, float depth, Color color);
Model createSingleModel(char tiles[sizeY][sizeX], int floors, Vector3 pos = { 0 });

Vector3 Vector3MoveTowards(Vector3 v, Vector3 target, float maxDistance);

Vector3 GetCameraForward(Camera* camera);
Vector3 GetCameraUp(Camera* camera);
Vector3 GetCameraRight(Camera* camera);

// Camera movement
void CameraMoveForward(Camera* camera, float distance, bool moveInWorldPlane);
void CameraMoveUp(Camera* camera, float distance);
void CameraMoveRight(Camera* camera, float distance, bool moveInWorldPlane);
void CameraMoveToTarget(Camera* camera, float delta);

// Camera rotation
void CameraYaw(Camera* camera, float angle, bool rotateAroundTarget);
void CameraPitch(Camera* camera, float angle, bool lockView, bool rotateAroundTarget, bool rotateUp);

Matrix GetCameraViewMatrix(Camera* camera);
Matrix GetCameraProjectionMatrix(Camera* camera, float aspect);

void UpdateCameraNew(Camera* camera, int mode);