#include "gui.h"

// Button //
Button::Button()
{
	size = { 0 };
}

Texture2D Button::getTexture()
{
	return texture;
}

void Button::setPos(int x, int y)
{
	pos = { (float)x, (float)y };
}

void Button::setSize(int width, int height)
{
	size = { (float)width, (float)height };
}

void Button::setText(std::string newText)
{
	text = newText;
}

void Button::setColor(Color color)
{
	col = color;
}

void Button::setFunc(std::function<void()> func) 
{
	function_ = func;
}

void Button::DrawButton(bool drawText)
{
	if (drawText)
	{
		DrawRectangle(pos.x, pos.y, size.x, size.y, col);
		DrawText(text.c_str(), pos.x + 3, pos.y, 20, WHITE);
	}
	else
	{
		DrawTexture(texture, pos.x, pos.y, RAYWHITE);
	}
}

void Button::DrawButton(float size)
{
	DrawTextureEx(texture, pos, 0, size, RAYWHITE);
}

void Button::Clicked(Vector2 MousePos)
{
	if (size.x == -1)
	{
		if (MousePos.x < pos.x + texture.width && MousePos.x > pos.x &&
			MousePos.y < pos.y + texture.height && MousePos.y > pos.y)
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				function_();
	}
	else
	{
		if (MousePos.x < pos.x + size.x && MousePos.x > pos.x &&
			MousePos.y < pos.y + size.y && MousePos.y > pos.y)
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				function_();
	}

}

void Button::Clicked()
{
	Clicked(GetMousePosition());
}

void Button::Unload()
{
	UnloadTexture(texture);
}