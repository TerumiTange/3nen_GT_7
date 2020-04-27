#include "Goal.h"

Goal::Goal(const Vector2& pos, const char* tag) :
	Actor(tag),
	mPos(new Vector2(0, 0)),
	mSize(new Vector2(32, 32)),
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
