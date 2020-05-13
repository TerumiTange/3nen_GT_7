#pragma once
#include "Actor.h"
#include "../Device/Renderer.h"
#include "../Utility/Vector2.h"

class Goal :
	public Actor
{
public:
	Goal(const Vector2& pos, const char* tag = "Goal");
	~Goal();
	virtual void End()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void Hit(std::list<std::shared_ptr<Actor>>)override;
	virtual void Hit(const char* tag, std::shared_ptr<Vector2> pos, std::shared_ptr<Vector2> size)override;
private:
	Vector2* mPos;
	Vector2* mSize;
	const char* mFilename;
	Renderer* mRenderer;

};