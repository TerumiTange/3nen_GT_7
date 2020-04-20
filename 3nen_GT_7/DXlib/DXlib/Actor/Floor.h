#pragma once
#include "Actor.h"
#include "../Utility/Vector2.h"
#include "../Device/Renderer.h"

class Floor :
	public Actor
{
public:
	Floor(const Vector2& position, const char* tag = "Floor");
	~Floor();
	virtual void Update()override;
	virtual void Draw()override;
	virtual void Hit(std::list<std::shared_ptr<Actor>>)override;
private:
	Vector2* mPos;
	const char* mFilename;
	Renderer* mRenderer;
};