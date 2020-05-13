#pragma once

#include "Actor.h"
#include "../System/Input.h"
#include "../Utility/Vector2.h"
#include "../Device/Renderer.h"

class DeathBlock :
	public Actor
{
public:
	DeathBlock(const Vector2& pos, const char* tag = "DeathBlock");
	~DeathBlock();
	virtual void End()override;
	virtual void Update()override;
	virtual void Draw() override;
	virtual void Hit(std::list<std::shared_ptr<Actor>> actors)override;
	virtual void Hit(const char* tag, std::shared_ptr<Vector2> pos, std::shared_ptr<Vector2> size)override;
private:
	Vector2* mPos;
	Vector2* mSize;
	//Renderer* mRenderer();
};