#pragma once
#include "../Utility/Vector2.h"
#include "../Device/Renderer.h"

class Wall
{
public:
	Wall(Vector2* pos, const char* tag = "Wall");
	~Wall();
	void Update();
	void Draw();

public:
	Vector2* position;
	const char* filename;
	Renderer renderer;
};