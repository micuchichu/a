#pragma once

#include "raylib.h"
#include <iostream>

class Scene
{
public:
	virtual void Draw();
	virtual void Update();
	virtual void BackgroundUpdates() = 0;
	virtual void OnSwitch() = 0;
private:
	bool active;
};