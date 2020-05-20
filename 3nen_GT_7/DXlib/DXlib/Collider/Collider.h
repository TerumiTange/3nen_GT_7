#pragma once
#include "Component.h"
#include "../Utility/Vector2.h"
#include <list>

class Actor;
class Physics;

class Collider : public Component
{
protected:
	Collider(Actor* owner);
	virtual ~Collider();
public:
	virtual void start() override;
	virtual void StartCollider() = 0;
	virtual void update() override;
	virtual void UpdateCollider() = 0;
	virtual void onUpdate() override;
	virtual void onUpdateCollider() = 0;
	bool getEnable() const;
	void AddHitCollider(Collider* hit);
	std::list<Collider*> onCollisionEnter();
	std::list<Collider*> onCollisionStay();
	std::list<Collider*> onCollisionExit();

	static void setPhysics(Physics* physics);

private:
	bool mEnable;
	std::list<Collider*> mPreviousCollider;
	std::list<Collider*> mCurrentCollider;

	static Physics* mPhysics;
};