#include "Actor.h"
#include "Collider.h"
#include "../Utility/Rect.h"

Collider::Collider(Actor* owner):
	mOwner(owner)//,
	//mRect(new Rect(*mOwner->Position(), *new Vector2(32,32)))//*size
{
}

Collider::~Collider()
{
}

void Collider::Update()
{
	
}

void Collider::RUpdate()
{
	/*for (const auto& c : mCurrentCollider)
	{
		if (mRect->Intersect(*c->mRect))
		{
			AddHitCollider(c);
		}
	}*/
	//‚ ‚½‚Á‚Ä‚¢‚ê‚Î
	//AddHitCollider();
}

Actor* Collider::GetOwner() const
{
	return mOwner;
}

std::list<Collider*> Collider::onCollisionEnter()
{
	std::list<Collider*> temp;

	return temp;
}
