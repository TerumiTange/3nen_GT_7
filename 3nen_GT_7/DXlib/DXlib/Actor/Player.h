#pragma once
#include "Actor.h"
#include "../System/Input.h"
#include "../Utility/Vector2.h"
#include "../Device/Renderer.h"
#include "../System/CountDownTimer.h"

class Player:
	public Actor
{
public :
	Player(const Vector2& position, const char* tag = "Player");
	~Player();
	virtual void End()override;
	virtual void Update()override;//更新
	void Fall();
	void Move();
	void Movement();//移動量計算
	void MovingFast();//瞬間移動
	virtual void Draw() override;
	void Damage();//ダメージ計算
	void Recovery();//回復
	void SetPosition(const Vector2& position);
	Vector2& GetPosition();
	virtual void Hit(std::list<std::shared_ptr<Actor>> actors)override;
	bool CheckHit(int x, int y, int width, int height);//あたっているかどうか
	bool CheckHitF(int x, int y, int width, int height);//高速移動中に当たっているかどうか
	bool RGoal();//ゴールしたかどうか
	bool GetMovingFast();//瞬間移動中かどうか

private:
	int mHp;//体力
	int mMaxHp;//最大体力
	float mInvincibleTime;//無敵時間
	bool mGoal;//ゴールしたかどうか
	Vector2* mPos;//ポジション
	Vector2* mVelocity;//ベクトル
	float maxSpeed;//最大速度
	float mAcceleration;//加速度
	Vector2* mSize;//大きさ
	const char* mFilename;//画像名
	Renderer* mRenderer;//描画関数
	Renderer* mStaticElectricity;//静電気画像
	Input* mInput;//キー入力
	CountDownTimer* mCountTimer;//カウントダウンタイマー
	bool mFall;//落ちているかどうか
	
	bool mMovingFast;//高速移動してるかどうか
	int mMovingFastCount;//高速移動のカウント
	float mMovingFastTime;//高速移動回復時間
	CountDownTimer* mMovingFastTimer;//高速移動回復用タイマー
	int mMovingFastAmount;//高速移動の移動量
	Vector2 mMovingFastDifference;//高速移動後の位置の差分
	CountDownTimer* mNowMovingFastTimer;//高速移動状態のタイマー
	bool mNowMovingFast;//高速移動した瞬間

	//瞬間移動は一定距離移動

	//bool mJump;//ジャンプしているかどうか
	//bool mFloating;//浮遊しているかどうか
	//int mElectricity;//自身の電気ゲージの量
	//bool mChargedState;//帯電状態かどうか
	//bool mPoppedState;//はじけ状態かどうか
	

	int old_x;
	int old_y;
};