#include "Actor.h"
#include "Collider.h"
#include "../Utility/Rect.h"

Collider::Collider(Actor* owner):
	mOwner(owner)//,
	//mRect(new Rect(*mOwner->Position(), *size))
{
}

Collider::~Collider()
{
}

void Collider::Update()
{
	mPreviousCollider.resize(mCurrentCollider.size());//サイズを同じにする
	std::copy(mCurrentCollider.begin(), mCurrentCollider.end(), mPreviousCollider.begin()); //mCurrentColliderの中身をmPreviousColliderにコピー
	mCurrentCollider.clear();//中身を削除
}

void Collider::RUpdate()
{
}

Actor* Collider::GetOwner() const
{
	return mOwner;
}

void Collider::AddHitCollider(Collider * hit)
{
	mCurrentCollider.emplace_back(hit);
}

std::list<Collider*> Collider::onCollisionEnter()
{
	std::list<Collider*> temp;
	for (const auto& c : mCurrentCollider) //mCurrentColliderの中身を回す
	{
		auto itr = std::find(mPreviousCollider.begin(), mPreviousCollider.end(), c);
		if (itr == mPreviousCollider.end()) 
		{
			temp.emplace_back(c);
		}
	}
	return temp;
}
