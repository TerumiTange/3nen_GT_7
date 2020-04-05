#include "Wall.h"


Wall::Wall(const Vector2& pos, const char* tag):
	position(new Vector2(0,0)),
	filename(tag),
	renderer()
{
	position->x = pos.x;
	position->y = pos.y;
}

Wall::~Wall()
{
}

void Wall::Update()
{
}

void Wall::Draw()
{
	//renderer.Draw(filename, *position);
	int a;
	a = LoadGraph("./Assets/Texture/Wall.png");
	DrawGraph(position->x, position->y, a, TRUE);
	DeleteGraph(a);
}
