#pragma once
#include "Actor.h"
#include "../Utility/Vector2.h"

//ÉvÉåÅ[ÉÑÅ[Çí«Ç¢Ç©ÇØÇÈ
class TestEnemy :
	public Actor
{
public:
	TestEnemy(const Vector2& position, const char* tag);
	~TestEnemy();
	void Init();
	virtual void Update()override;
	virtual void Draw() override;
	virtual void Hit(std::list<std::shared_ptr<Actor>>actor)override;
	void setPos(const Vector2& pos);
private:
	Vector2* mPos;
	const char* mFilename;
	bool mFall;
};