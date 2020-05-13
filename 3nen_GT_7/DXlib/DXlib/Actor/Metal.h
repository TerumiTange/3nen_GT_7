#pragma once
#include "Actor.h"
#include "../Utility/Vector2.h"
#include "../Device/Renderer.h"

class Metal:
	public Actor
{
public:
	Metal(const Vector2& pos, const char* tag = "Metal");
	~Metal();
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
