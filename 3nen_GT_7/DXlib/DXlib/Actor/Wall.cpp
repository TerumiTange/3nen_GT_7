#include "Wall.h"


Wall::Wall(Vector2 pos, const char* tag):
	position(&pos),
	filename(tag),
	renderer()
{
}

Wall::~Wall()
{
}

void Wall::Update()
{
}

void Wall::Draw()
{
	renderer.Draw(filename, *position);
}
