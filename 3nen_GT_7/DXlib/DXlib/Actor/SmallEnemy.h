#pragma once
#include "Actor.h"
#include "../Utility/Vector2.h"
class Renderer;

class SmallEnemy :
	public Actor
{
public:
	SmallEnemy(const Vector2& pos, const char* tag = "SmallEnemy");
	~SmallEnemy();
	virtual void Update()override;
	virtual void Draw()override;
	virtual void Hit(std::list<std::shared_ptr<Actor>>actors)override;
	bool CheckHit(int x, int y, int width, int height);

private:
	Vector2* mPos;
	Vector2* mSize;
	const char* mFilename;
	Renderer* renderer;
	bool mFall;
	bool mRight;//右に進んでいるかどうか
	//仮の数値
	int old_x;//1フレーム前の位置
	int old_y;//1フレーム前の位置
};