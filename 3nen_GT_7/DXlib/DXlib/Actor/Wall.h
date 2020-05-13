#pragma once
#include "Actor.h"
#include "../Utility/Vector2.h"
#include "../Device/Renderer.h"

class Wall:
	public Actor
{
public:
	Wall(const Vector2& position, const char* tag = "Wall");
	~Wall();
	virtual void End()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void Hit(std::list<std::shared_ptr<Actor>>)override;
	virtual void Hit(const char* tag, std::shared_ptr<Vector2> pos, std::shared_ptr<Vector2> size)override;
public:
	Vector2* mPos;
	Vector2* mSize;
	const char* mFilename;
	Renderer* mRenderer;

};