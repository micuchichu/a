#pragma once
#pragma once

#include "raylib.h"
#include <functional>
#include <iostream>

class Button
{
public:
	Button();

	Button(Texture2D texture)
		: texture(texture) {}

	Button(float x, float y)
		: pos({ x, y }) {}

	Button(std::function<void()> func)
		: function_(func) {}

	Button(Vector2 pos, Vector2 size, std::string text, Color col)
		: pos(pos), size(size), text(text), col(col) {}

	Texture2D getTexture();

	void setPos(int x, int y);

	void setSize(int width, int height);

	void setText(std::string text);

	void setColor(Color col);
	
	void setFunc(std::function<void()> func);

	void DrawButton(bool drawText = false);

	void DrawButton(float size);

	void Clicked(Vector2 MousePos);

	void Clicked();

	void Unload();

private:
	Texture2D texture;
	Color col;
	std::string text;
	Vector2 size;
	Vector2 pos;
	std::function<void()> function_;
};