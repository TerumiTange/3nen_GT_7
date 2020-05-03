#include "DeathBlock.h"

DeathBlock::DeathBlock(const Vector2& pos, const char* tag) :
	Actor(tag),
	mPos(new Vector2()),
	mSize(new Vector2(32,32))//,
	//mRenderer(new Renderer(tag))
{
	*mPos = pos;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
}

DeathBlock::~DeathBlock() = default;

void DeathBlock::End()
{
	delete(mPos);
	delete(mSize);
	//delete(mRenderer);
}

void DeathBlock::Update()
{
}

void DeathBlock::Draw()
{

}

void DeathBlock::Hit(std::list<std::shared_ptr<Actor>> actors)
{
}

