#pragma once
#include "Actor.h"
#include "../Utility/Vector2.h"
#include "../Device/Renderer.h"
#include "../Collider/ColliderComponent.h"

class Wall:
	public Actor
{
public:
	Wall(const Vector2& position, const char* tag = "Wall");
	~Wall();
	virtual void End()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void Hit() override;
public:
	Vector2* mPos;
	Vector2* mSize;
	const char* mFilename;
	Renderer* mRenderer;
	ColliderComponent* mCollider;
};