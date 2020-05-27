#include "Actor.h"
#include "ActorManager.h"
#include "../Utility/Vector2.h"
#include "../Collider/ComponentManager.h"
#include "../System/CountDownTimer.h"

Actor::Actor(const char * tag):
	mComponentManager(std::make_shared<ComponentManager>()),
	mPos(std::make_shared<Vector2>()),
	mSize(std::make_shared<Vector2>()),
	mDestroyTimer(nullptr),
	mState(ActorState::ACTIVE),
	mTag(tag),
	mElectricShock(false)
{
	death = false;
    if (mActorManager) 
    {
    	mActorManager->Add(this);
    }
}

Actor::~Actor() = default;

void Actor::update()
{
	mComponentManager->start();
	if (mState == ActorState::ACTIVE)
	{
		DestroyTimer();
		mComponentManager->update();
		if (!death)
		{
			Update();
		}
		
		mComponentManager->onUpdate();
		
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

void Actor::Destroy(Actor * actor, float sec)
{
	if (actor->mDestroyTimer)return;
	actor->mDestroyTimer = std::make_unique<CountDownTimer>(sec);
}

void Actor::Destroy(std::shared_ptr<Actor> actor, float sec)
{
	if (actor->mDestroyTimer)return;
	actor->mDestroyTimer = std::make_unique<CountDownTimer>(sec);
}

std::shared_ptr<ComponentManager> Actor::componentManager() const
{
	return mComponentManager;
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

void Actor::SetElectricShock(bool f)
{
	mElectricShock = f;
}

bool Actor::GetElectricShock()
{
	return mElectricShock;
}

void Actor::SetActorManager(ActorManager * manager)
{
	mActorManager = manager;
}

ActorManager* Actor::GetActorManager()
{
	return mActorManager;
}

void Actor::DestroyTimer()
{
	if (!mDestroyTimer)return;
	death = true;
	mDestroyTimer->Update();
	if (mDestroyTimer->IsTime())
	{
		mState = ActorState::DEAD;
	}
}

ActorManager* Actor::mActorManager = nullptr;

CountDownTimer* Actor::mElectricTimer = new CountDownTimer();