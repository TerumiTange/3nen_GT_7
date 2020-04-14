#pragma once
#include "Actor.h"
#include "../Utility/Vector2.h"
#include "../Device/Renderer.h"
#include "Collider.h"

class Wall:
	public Actor
{
public:
	Wall(const Vector2& position, const char* tag = "Wall");
	~Wall();
	virtual void Update()override;
	virtual void Draw()override;

public:
	Vector2* pos;
	const char* filename;
	Renderer renderer;

private:
	Collider* mCollider;
};