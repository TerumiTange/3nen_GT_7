#include "Collider.h"
#include "Physics.h"
#include <algorithm>

Collider::Collider(Actor* owner) :
	Component(owner, 1000),
	mEnable(false)
{
}

Collider::~Collider()
{
	if (mPhysics)
	{
		mPhysics->remove(this);
	}
}

void Collider::start()
{
	StartCollider();
	if (mPhysics)
	{
		mPhysics->add(this);
		mEnable = true;
	}
}

void Collider::update()
{
	UpdateCollider();
	mPreviousCollider.resize(mCurrentCollider.size());
	std::copy(mCurrentCollider.begin(), mCurrentCollider.end(), mPreviousCollider.begin());
	mCurrentCollider.clear();
}

void Collider::onUpdate()
{
	onUpdateCollider();
}

bool Collider::getEnable() const
{
	return mEnable;
}

void Collider::AddHitCollider(Collider * hit)
{
	mCurrentCollider.emplace_back(hit);
}

std::list<Collider*> Collider::onCollisionEnter()
{
	std::list<Collider*> temp;
	for (const auto& c : mCurrentCollider) {
		auto itr = std::find(mPreviousCollider.begin(), mPreviousCollider.end(), c);//first����end�܂ł̊Ԃ�c�Ɠ����l��T��
		if (itr == mPreviousCollider.end()) {
			temp.emplace_back(c);
		}
	}

	return temp;
}

void Collider::setPhysics(Physics * physics)
{
	mPhysics = physics;
}

Physics* Collider::mPhysics = nullptr;