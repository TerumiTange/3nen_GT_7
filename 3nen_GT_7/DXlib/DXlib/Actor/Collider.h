#pragma once
#include "../Device/Dx.h"
#include <list>

class Vector2;
class Actor;

class Collider
{
public:
	Collider(Actor* owner);
	~Collider();
	void Update();
	void RUpdate();//ëçìñÇΩÇËîªíË
	Actor* GetOwner() const;
	//void AddHitCollider(Collider* hit);
	std::list<Collider*> onCollisionEnter();
private:
	std::list<Collider*> mPreviousCollider;
	std::list<Collider*> mCurrentCollider;
	Actor* mOwner;
};