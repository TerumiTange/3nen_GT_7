#pragma once
#include "Actor.h"
#include "../System/Input.h"
#include "../Utility/Vector2.h"
#include "../Device/Renderer.h"
#include "../System/CountDownTimer.h"
#include "../System/CountUpTimer.h"
#include "../Device/Sound.h"
#include "../Collider/ColliderComponent.h"

class Player:
	public Actor
{
public :
	Player(const Vector2& position, const char* tag = "Player");
	~Player();
	virtual void End()override;
	virtual void Update()override;//更新
	void Fall();//重力
	void Move();//操作
	void Movement();//移動量計算
	void MovingFast();//瞬間移動
	virtual void Draw() override;//描画
	void Damage();//ダメージ計算
	void Recovery();//回復
	void SetPosition(const Vector2& position);//その位置座標に移動させる
	Vector2& GetPosition();//現在の位置座標を渡す
	virtual void Hit() override;
	bool GetMovingFast();//瞬間移動中かどうか

private:
	ColliderComponent* mCollider;
	int mHp;//体力
	int mMaxHp;//最大体力
	float mInvincibleTime;//無敵時間
	Vector2* mPos;//ポジション
	Vector2* mVelocity;//ベクトル
	float maxSpeed;//最大速度
	float mAcceleration;//加速度
	Vector2* mSize;//大きさ
	const char* mFilename;//画像名
	Renderer* mRenderer;//描画関数
	Renderer* mIdolRenderer;//アイドル状態描画
	Renderer* mStaticElectricity;//静電気画像
	Renderer* mHeart;//ハートの画像（HP）
	Renderer* mNumber;//高速移動回数用
	Input* mInput;//キー入力
	CountDownTimer* mCountTimer;//カウントダウンタイマー
	bool mFall;//落ちているかどうか
	float mGravity;//重力のスピード
	float mMovingFastGravity;//高速移動中の重力
	
	bool mMovingFast;//高速移動してるかどうか
	int mMovingFastCount;//高速移動のカウント
	int mMovingFastMaxCount;//最大高速移動の回数

	int mMovingFastAmount;//高速移動の移動量
	CountDownTimer* mNowMovingFastTimer;//高速移動状態のタイマー
	float mNowMovingFastTime;//高速移動状態の時間
	bool mNowMovingFast;//高速移動した瞬間

	bool mRight;//右を向いているかどうか

	Sound* sound;

	Renderer* mContent;//回数の中身
	Renderer* mFrame;//回数の周り
	CountUpTimer* mUpTimer;

	int old_x;//動く前のX座標
	int old_y;//動く前のY座標
};