#pragma once

#include "raylib.h"
#include "globals.h"

#include <cmath>

void fillDFS(int x, int y, char oldColor, char newColor, char tiles[sizeX][sizeY]);

void UpdateTransform(Model& model, Vector3 newPos);

Vector3 Vector3Normalize(Vector3 v);

Matrix MatrixMultiply(Matrix left, Matrix right);

Matrix MatrixTranslate(float x, float y, float z);

Matrix MatrixRotate(Vector3 axis, float angle);