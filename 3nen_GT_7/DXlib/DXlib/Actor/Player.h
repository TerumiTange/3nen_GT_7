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
	void Fall();//重力
	void Move();//操作
	void Movement();//移動量計算
	void MovingFast();//瞬間移動
	virtual void Draw() override;//描画
	void Damage();//ダメージ計算
	void Recovery();//回復
	void SetPosition(const Vector2& position);//その位置座標に移動させる
	Vector2& GetPosition();//現在の位置座標を渡す
	virtual void Hit(std::list<std::shared_ptr<Actor>> actors)override;//当たり判定
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
	float mGravity;//重力のスピード
	float mMovingFastGravity;//高速移動中の重力
	
	bool mMovingFast;//高速移動してるかどうか
	int mMovingFastCount;//高速移動のカウント
	int mMovingFastMaxCount;//最大高速移動の回数
	float mMovingFastTime;//高速移動回復時間
	CountDownTimer* mMovingFastTimer;//高速移動回復用タイマー
	int mMovingFastAmount;//高速移動の移動量
	//Vector2* mMovingFastDifference;//高速移動後の位置の差分
	float mMovingFastDifferenceX;//高速移動後の位置差分X
	float mMovingFastDifferenceY;//高速移動後の位置差分Y
	CountDownTimer* mNowMovingFastTimer;//高速移動状態のタイマー
	float mNowMovingFastTime;//高速移動状態の時間
	bool mNowMovingFast;//高速移動した瞬間

	CountDownTimer* mFallTimer;//重力軽減の時間タイマー
	float mFallTime;//重力軽減の時間

	//瞬間移動は一定距離移動

	//bool mJump;//ジャンプしているかどうか
	//bool mFloating;//浮遊しているかどうか
	//int mElectricity;//自身の電気ゲージの量
	//bool mChargedState;//帯電状態かどうか
	//bool mPoppedState;//はじけ状態かどうか
	

	int old_x;//動く前のX座標
	int old_y;//動く前のY座標
};