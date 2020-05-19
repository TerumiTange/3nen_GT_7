#pragma once
#include "Actor.h"
#include "../Utility/Vector2.h"
#include "../Device/Renderer.h"
#include "../Collider/ColliderComponent.h"

class Floor :
	public Actor
{
public:
	Floor(const Vector2& position, const char* tag = "Floor");
	~Floor();
	virtual void End()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void Hit() override;
private:
	Vector2* mPos;
	Vector2* mSize;
	const char* mFilename;
	Renderer* mRenderer;
	ColliderComponent* mCollider;
};