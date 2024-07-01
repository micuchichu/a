#include "gui.h"

// Button //
Texture2D Button::getTexture()
{
	return texture;
}

void Button::setPos(int x, int y)
{
	pos = { (float)x, (float)y };
}

void Button::setFunc(std::function<void()> func) {
	function_ = func;
}

void Button::DrawButton()
{
	DrawTexture(texture, pos.x, pos.y, RAYWHITE);

}

void Button::DrawButton(float size)
{
	DrawTextureEx(texture, pos, 0, size, RAYWHITE);
}

void Button::Clicked(Vector2 MousePos)
{
	if (MousePos.x < pos.x + texture.width && MousePos.x > pos.x &&
		MousePos.y < pos.y + texture.height && MousePos.y > pos.y)
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			function_();
}

void Button::Clicked()
{
	Clicked(GetMousePosition());
}

void Button::Unload()
{
	UnloadTexture(texture);
}