#include "Metal.h"

Metal::Metal(const Vector2& pos, const char* tag) :
	Actor(tag),
	mPos(new Vector2(0, 0)),
	mSize(new Vector2(32, 32)),
	mFilename(tag),
	mRenderer(new Renderer())
{
	*mPos = pos;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
}

Metal::~Metal()
{
}

void Metal::End()
{
	delete(mPos);
	delete(mSize);
	delete(mRenderer);
}

void Metal::Update()
{
}

void Metal::Draw()
{
	mRenderer->Draw(mFilename, *mPos);
}

void Metal::Hit(std::list<std::shared_ptr<Actor>>)
{
}
