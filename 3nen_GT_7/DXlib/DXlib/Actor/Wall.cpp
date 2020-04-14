#include "Wall.h"


Wall::Wall(const Vector2& position, const char* tag):
	Actor(tag),
	pos(new Vector2(0,0)),
	filename(tag),
	renderer(*new Renderer()),
	mCollider(new Collider(this))
{
	pos->x = position.x;
	pos->y = position.y;
	Actor::SetPos(*pos);
}

Wall::~Wall() = default;

void Wall::Update()
{
}

void Wall::Draw()
{
	//renderer.Draw(filename, *position);
	int a;
	a = LoadGraph("./Assets/Texture/Wall.png");
	DrawGraph(pos->x, pos->y, a, TRUE);
	DeleteGraph(a);
}
