#include "ColliderComponent.h"
#include "../Actor/Actor.h"


ColliderComponent::ColliderComponent(Actor* owner) :
	Collider(owner),
	mQuadrangle(nullptr),
	mIsAutoUpdate(true)
{

}

ColliderComponent::~ColliderComponent() = default;

void ColliderComponent::StartCollider()
{
	//auto a = Vector2(mOwner->Position()->x, mOwner->Position()->y);
	//auto b = Vector2(mOwner->Size()->x, mOwner->Size()->y);
	mQuadrangle = std::make_shared<Quadrangle>(mOwner->Position()->Vec(), mOwner->Size()->Vec());
}

void ColliderComponent::UpdateCollider()
{
}

void ColliderComponent::onUpdateCollider()
{
	if (!mIsAutoUpdate)
	{
		return;
	}
	//mOwner;
	//auto a = Vector2(mOwner->Position()->x, mOwner->Position()->y);
	//auto b = Vector2(mOwner->Size()->x, mOwner->Size()->y);
	mQuadrangle->set(mOwner->Position()->Vec(), mOwner->Size()->Vec());
}

void ColliderComponent::Set(const Vector2& pos, const Vector2& size)
{
	mQuadrangle->set(pos, size);
	if (mIsAutoUpdate)
	{
		mIsAutoUpdate = false;
	}
}

std::shared_ptr<Quadrangle> ColliderComponent::getQuadrangle() const
{
	return mQuadrangle;
}

void ColliderComponent::automation()
{
	if (!mIsAutoUpdate)
	{
		mIsAutoUpdate = true;
	}
}
