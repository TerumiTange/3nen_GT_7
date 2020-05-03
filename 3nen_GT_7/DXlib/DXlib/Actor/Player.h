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
	void Init();
	virtual void Update()override;
	void Fall();
	void Jump();
	void Floating();
	virtual void Draw() override;
	void Move();
	void Damage();
	void SetPosition(const Vector2& position);
	Vector2& GetPosition();
	virtual void Hit(std::list<std::shared_ptr<Actor>> actors)override;
	bool CheckHit(int x, int y, int width, int height);
	bool RGoal();//ゴールしたかどうか

private:
	int mHp;//体力
	int mMaxHp;//最大体力
	float mInvincibleTime;//無敵時間
	bool mGoal;//ゴールしたかどうか
	Vector2* mPos;//
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
	bool mJump;//ジャンプしているかどうか
	bool mFloating;//浮遊しているかどうか
	int mElectricity;//自身の電気ゲージの量
	bool mChargedState;//帯電状態かどうか
	bool mPoppedState;//はじけ状態かどうか
	/*
	移動することで電気ゲージがたまる
	金属に触れると電気ゲージを0にして、はじけ状態になる
	はじけ状態だと反対方向に飛んでいく（一定）
	電気ゲージが100になってから10秒立つと帯電状態になる-＞本来は金属に近づくと発生
	帯電状態だと一度だけ次のアクションが2倍になる
	とりあえず
	*/
	int old_x;
	int old_y;
};