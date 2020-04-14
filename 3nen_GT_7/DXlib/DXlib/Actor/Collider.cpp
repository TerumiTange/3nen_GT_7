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
	mPreviousCollider.resize(mCurrentCollider.size());//�T�C�Y�𓯂��ɂ���
	std::copy(mCurrentCollider.begin(), mCurrentCollider.end(), mPreviousCollider.begin()); //mCurrentCollider�̒��g��mPreviousCollider�ɃR�s�[
	mCurrentCollider.clear();//���g���폜
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
	for (const auto& c : mCurrentCollider) //mCurrentCollider�̒��g����
	{
		auto itr = std::find(mPreviousCollider.begin(), mPreviousCollider.end(), c);
		if (itr == mPreviousCollider.end()) 
		{
			temp.emplace_back(c);
		}
	}
	return temp;
}
