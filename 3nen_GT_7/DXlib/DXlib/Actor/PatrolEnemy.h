#pragma once
#include "Actor.h"
#include "../Utility//Vector2.h"
#include "../Device/Renderer.h"
#include "../System/CountDownTimer.h"
#include "../Device/Sound.h"
#include "../Collider/ColliderComponent.h"
#include "../Collider/Component.h"

#include <memory>
#include <vector>


class Player;

class PatrolEnemy :public Actor
{
public:
	PatrolEnemy(const Vector2& pos, const char* tag = "PatrolEnemy");
	~PatrolEnemy();
	virtual void End()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void Hit()override;

	void ToPlayer();
	void Move();
	void Paralise();
	void Patrol();
	void PatrolMove();
	//bool CheckHit(int x, int y, int width, int height);
	//bool CheckHit2(int x, int y, int width, int height,int p);
	//void Stalker();

private:
	ColliderComponent* mCollider;
	Vector2* mPos;
	Vector2* mSize;
	const char* mFilename;
	Renderer* mRenderer;//アイドル状態の画像
	bool mFall;
	bool mRight;//右に進んでいるかどうか？
	//仮の数値
	int old_x;//1フレーム前のｘ位置
	int old_y;//1フレーム前のｙ位置

	bool mStalker;//trueで追跡状態に
	Vector2 pPos;
	Vector2 direction;
	int staSize;//追跡範囲
	Renderer* sRenderer;//追跡状態の画像
	Renderer* paralRenderer;//マヒ状態の画像
	float speed;//追いかける速度
	float paraTime;
	CountDownTimer* paralimitTime;
	bool paral;
	CountDownTimer* playerHitTimer;//プレイヤーと連続で当たらないためのタイマー
	CountDownTimer* paralimitTimer;//連続で麻痺状態にならないためのタイマー

	Sound* sound;//音
	//Vector2* patrolPos[];
	std::vector<Vector2> patrolPos;
	bool mPatrol;
	int patrolcount;
	Vector2 a;
	float pspeed;
	CountDownTimer* mUpTimer;
};