#pragma once

#include "Collider.h"
#include "Collision.h"
#include "../Utility/Vector2.h"
#include <memory>

class Actor;
//class Vector2;

class ColliderComponent :public Collider
{
public:
	ColliderComponent(Actor* owner);
	~ColliderComponent();
	virtual void StartCollider() override;
	virtual void UpdateCollider() override;
	virtual void onUpdateCollider() override;
	void Set(const Vector2& pos, const Vector2& size);
	std::shared_ptr<Quadrangle> getQuadrangle() const;
	void automation();

private:
	std::shared_ptr<Quadrangle> mQuadrangle;
	bool mIsAutoUpdate;
};