#include "utils.h"

void fillDFS(int x, int y, char oldColor, char newColor, char tiles[sizeX][sizeY])
{
	if (x < 0 || x >= sizeX || y < 0 || y >= sizeY || tiles[y][x] != oldColor || tiles[y][x] == newColor)
		return;

	tiles[y][x] = newColor;

	fillDFS(x + 1, y, oldColor, newColor, tiles);
	fillDFS(x - 1, y, oldColor, newColor, tiles);
	fillDFS(x, y + 1, oldColor, newColor, tiles);
	fillDFS(x, y - 1, oldColor, newColor, tiles);
}

void UpdateTransform(Model& model, Vector3 pos)
{
	Matrix translation = MatrixTranslate(pos.x, pos.y, pos.z);
	Vector3 axis = Vector3Normalize({ 0, 0, 0 });
	float angle = 0;
	Matrix rotation = MatrixRotate(axis, angle);

	model.transform = MatrixMultiply(rotation, translation);
}

// ********** IMPORTANT NOTE **************
// 
// The functions below are taken from
// raylib's source code as i was too lazy
// to update the library
// 
// ****** THANK YOU FOR READING THIS ******

Vector3 Vector3Normalize(Vector3 v)
{
	Vector3 result = v;

	float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length == 0.0f) length = 1.0f;
	float ilength = 1.0f / length;

	result.x *= ilength;
	result.y *= ilength;
	result.z *= ilength;

	return result;
}

Matrix MatrixMultiply(Matrix left, Matrix right)
{
	Matrix result = { 0 };

	result.m0 = left.m0 * right.m0 + left.m1 * right.m4 + left.m2 * right.m8 + left.m3 * right.m12;
	result.m1 = left.m0 * right.m1 + left.m1 * right.m5 + left.m2 * right.m9 + left.m3 * right.m13;
	result.m2 = left.m0 * right.m2 + left.m1 * right.m6 + left.m2 * right.m10 + left.m3 * right.m14;
	result.m3 = left.m0 * right.m3 + left.m1 * right.m7 + left.m2 * right.m11 + left.m3 * right.m15;
	result.m4 = left.m4 * right.m0 + left.m5 * right.m4 + left.m6 * right.m8 + left.m7 * right.m12;
	result.m5 = left.m4 * right.m1 + left.m5 * right.m5 + left.m6 * right.m9 + left.m7 * right.m13;
	result.m6 = left.m4 * right.m2 + left.m5 * right.m6 + left.m6 * right.m10 + left.m7 * right.m14;
	result.m7 = left.m4 * right.m3 + left.m5 * right.m7 + left.m6 * right.m11 + left.m7 * right.m15;
	result.m8 = left.m8 * right.m0 + left.m9 * right.m4 + left.m10 * right.m8 + left.m11 * right.m12;
	result.m9 = left.m8 * right.m1 + left.m9 * right.m5 + left.m10 * right.m9 + left.m11 * right.m13;
	result.m10 = left.m8 * right.m2 + left.m9 * right.m6 + left.m10 * right.m10 + left.m11 * right.m14;
	result.m11 = left.m8 * right.m3 + left.m9 * right.m7 + left.m10 * right.m11 + left.m11 * right.m15;
	result.m12 = left.m12 * right.m0 + left.m13 * right.m4 + left.m14 * right.m8 + left.m15 * right.m12;
	result.m13 = left.m12 * right.m1 + left.m13 * right.m5 + left.m14 * right.m9 + left.m15 * right.m13;
	result.m14 = left.m12 * right.m2 + left.m13 * right.m6 + left.m14 * right.m10 + left.m15 * right.m14;
	result.m15 = left.m12 * right.m3 + left.m13 * right.m7 + left.m14 * right.m11 + left.m15 * right.m15;

	return result;
}

Matrix MatrixTranslate(float x, float y, float z)
{
	Matrix result = { 1.0f, 0.0f, 0.0f, x,
					  0.0f, 1.0f, 0.0f, y,
					  0.0f, 0.0f, 1.0f, z,
					  0.0f, 0.0f, 0.0f, 1.0f };

	return result;
}

Matrix MatrixRotate(Vector3 axis, float angle)
{
	Matrix result = { 0 };

	float x = axis.x, y = axis.y, z = axis.z;

	float lengthSquared = x * x + y * y + z * z;

	if ((lengthSquared != 1.0f) && (lengthSquared != 0.0f))
	{
		float ilength = 1.0f / sqrtf(lengthSquared);
		x *= ilength;
		y *= ilength;
		z *= ilength;
	}

	float sinres = sinf(angle);
	float cosres = cosf(angle);
	float t = 1.0f - cosres;

	result.m0 = x * x * t + cosres;
	result.m1 = y * x * t + z * sinres;
	result.m2 = z * x * t - y * sinres;
	result.m3 = 0.0f;

	result.m4 = x * y * t - z * sinres;
	result.m5 = y * y * t + cosres;
	result.m6 = z * y * t + x * sinres;
	result.m7 = 0.0f;

	result.m8 = x * z * t + y * sinres;
	result.m9 = y * z * t - x * sinres;
	result.m10 = z * z * t + cosres;
	result.m11 = 0.0f;

	result.m12 = 0.0f;
	result.m13 = 0.0f;
	result.m14 = 0.0f;
	result.m15 = 1.0f;

	return result;
}