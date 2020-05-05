#pragma once
#include "Actor.h"
#include "../Utility/Vector2.h"
#include "../Device/Renderer.h"

class FlyEnemy :public Actor
{
public:
	FlyEnemy(const Vector2& pos, const char* tag = "FlyEnemy");
	~FlyEnemy();
	virtual void End()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void Hit(std::list<std::shared_ptr<Actor>>actors)override;
	bool CheckHit(int x, int y, int width, int height);

	void Move();
	void Fall();
	void Stalker();

private:
	Vector2* mPos;
	Vector2* mSize;
	const char* mFilename;
	Renderer* mRenderer;//アイドル状態の画像
	bool mFall;
	bool mRight;//右に進んでいるかどうか
	//仮の数値
	int old_x;//1フレーム前の位置
	int old_y;//1フレーム前の位置

	bool mStalker;//trueで追跡状態に
	Vector2 pPos;
	Vector2 direction;
	Vector2* staSize;//追跡の範囲
	Renderer* sRenderer;//追跡状態の画像
	//Renderer* paralRenderer//マヒ状態の画像
	//float* speed;//追いかける速度
};