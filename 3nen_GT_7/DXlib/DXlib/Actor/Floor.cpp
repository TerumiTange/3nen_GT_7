#include "Floor.h"

Floor::Floor(const Vector2& position, const char* tag) :
	Actor(tag),
	mPos(new Vector2(0,0)),
	mSize(new Vector2(32,32)),
	mFilename(tag),
	mRenderer(new Renderer(tag))
{
	*mPos = position;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
}

Floor::~Floor() = default;

void Floor::End()
{
	delete(mPos);
	delete(mSize);
	delete(mRenderer);
}

void Floor::Update()
{

}

void Floor::Draw()
{
	mRenderer->Draw(*mPos);
	//int a;
	//a = LoadGraph("./Assets/Texture/Floor.png");
	//DrawGraph(mPos->x, mPos->y, a, TRUE);
	//DeleteGraph(a);
}

void Floor::Hit(std::list<std::shared_ptr<Actor>>)
{
}

void Floor::Hit(const char * tag, std::shared_ptr<Vector2> pos, std::shared_ptr<Vector2> size)
{
}
