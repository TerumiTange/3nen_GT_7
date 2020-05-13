#include "Goal.h"

Goal::Goal(const Vector2& pos, const char* tag) :
	Actor(tag),
	mPos(new Vector2(0, 0)),
	mSize(new Vector2(64, 128)),
	mFilename(tag),
	mRenderer(new Renderer(tag))
{
	*mPos = pos;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
}

Goal::~Goal()
{
}

void Goal::End()
{
	delete(mPos);
	delete(mSize);
	delete(mRenderer);
}

void Goal::Update()
{
}

void Goal::Draw()
{
	mRenderer->Draw(*mPos);
}

void Goal::Hit(std::list<std::shared_ptr<Actor>>)
{
}

void Goal::Hit(const char * tag, std::shared_ptr<Vector2> pos, std::shared_ptr<Vector2> size)
{
}
