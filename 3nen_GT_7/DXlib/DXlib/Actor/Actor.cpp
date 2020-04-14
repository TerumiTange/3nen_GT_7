#include "Actor.h"
#include "ActorManager.h"
#include "../Utility/Vector2.h"

Actor::Actor(const char * tag):
	mPos(std::make_shared<Vector2>()),
	mSize(std::make_shared<Vector2>()),
	mState(ActorState::ACTIVE),
	mTag(tag)
{
    if (mActorManager) 
    {
    	mActorManager->Add(this);
    }
}

Actor::~Actor() = default;

void Actor::update()
{
	if (mState == ActorState::ACTIVE)
	{
		Update();
	}
}

void Actor::Destroy(Actor* actor)
{
	actor->mState = ActorState::DEAD;
}

void Actor::Destroy(std::shared_ptr<Actor> actor)
{
	actor->mState = ActorState::DEAD;
}

void Actor::SetPos(Vector2& position)
{
	*mPos = position;
}

void Actor::SetSize(Vector2 & size)
{
	*mSize = size;
}

std::shared_ptr<Vector2> Actor::Position() const
{
	return mPos;
}

std::shared_ptr<Vector2> Actor::Size() const
{
	return mSize;
}


ActorState Actor::GetState() const
{
	return mState;
}

const char* Actor::Tag() const
{
	return mTag;
}

void Actor::SetActorManager(ActorManager * manager)
{
	mActorManager = manager;
}

ActorManager* Actor::GetActorManager()
{
	return mActorManager;
}

ActorManager* Actor::mActorManager = nullptr;