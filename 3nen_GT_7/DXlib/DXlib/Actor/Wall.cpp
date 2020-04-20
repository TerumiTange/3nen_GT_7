#include "Wall.h"


Wall::Wall(const Vector2& position, const char* tag):
	Actor(tag),
	mPos(new Vector2(0,0)),
	mFilename(tag),
	mRenderer(new Renderer())//,
	//mCollider(new Collider(this))
{
	mPos->x = position.x;
	mPos->y = position.y;
	Actor::SetPos(*mPos);
	Actor::SetSize(*new Vector2(32, 32));
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
	DrawGraph(mPos->x, mPos->y, a, TRUE);
	DeleteGraph(a);
}

void Wall::Hit(std::list<std::shared_ptr<Actor>>)
{
}
