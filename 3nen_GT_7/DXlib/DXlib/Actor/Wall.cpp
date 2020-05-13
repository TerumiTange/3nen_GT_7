#include "Wall.h"


Wall::Wall(const Vector2& position, const char* tag):
	Actor(tag),
	mPos(new Vector2(0,0)),
	mSize(new Vector2(32,32)),
	mFilename(tag),
	mRenderer(new Renderer(tag))
{
	mPos->x = position.x;
	mPos->y = position.y;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
}

Wall::~Wall() = default;

void Wall::End()
{
	delete(mPos);
	delete(mSize);
	delete(mRenderer);
}

void Wall::Update()
{
}

void Wall::Draw()
{
	mRenderer->Draw(*mPos);
	//int a;
	//a = LoadGraph("./Assets/Texture/Wall.png");
	//DrawGraph(mPos->x, mPos->y, a, TRUE);
	//DeleteGraph(a);
}

void Wall::Hit(std::list<std::shared_ptr<Actor>>)
{
}

void Wall::Hit(const char * tag, std::shared_ptr<Vector2> pos, std::shared_ptr<Vector2> size)
{
}
