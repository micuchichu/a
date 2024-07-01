#pragma once
#pragma once

#include "raylib.h"
#include <functional>
#include <iostream>

class Button
{
public:
	Button() = default;

	Button(Texture2D texture)
		: texture(texture) {}

	Button(float x, float y)
		: pos({ x, y }) {}

	Button(std::function<void()> func)
		: function_(func) {}

	Texture2D getTexture();

	void setPos(int x, int y);

	void setFunc(std::function<void()> func);

	void DrawButton();

	void DrawButton(float size);

	void Clicked(Vector2 MousePos);

	void Clicked();

	void Unload();

private:
	Texture2D texture;
	Vector2 pos;
	std::function<void()> function_;
};