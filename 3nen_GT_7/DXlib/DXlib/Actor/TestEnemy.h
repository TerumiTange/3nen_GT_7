#pragma once
#include "Actor.h"
class Vector2;

class TestEnemy :
	public Actor
{
	TestEnemy(const Vector2& position, const char* tag);
	~TestEnemy();
	void Init();
	virtual void Update()override;
	virtual void Draw() override;
	virtual void Hit()override;
private:
	Vector2* mPos;
	const char* mFilename;
	bool mFall;
};