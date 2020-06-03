#pragma once
#include "Actor.h"
#include "../Utility//Vector2.h"
#include "../Device/Renderer.h"
#include "../System/CountDownTimer.h"
#include "../System/CountUpTimer.h"
#include "../Device/Sound.h"
#include "../Collider/ColliderComponent.h"
#include "../Collider/Component.h"

#include <memory>
#include <vector>

class Player;

class RushEnemy :public Actor
{
public:
	RushEnemy(const Vector2& pos, const char* tag = "RushEnemy");
	~RushEnemy();
	virtual void End()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void Hit()override;

	void DeathUpdate();
	void ToPlayer();
	void Move();
	void Rush();
	void Paralise();
	//bool CheckHit(int x, int y, int width, int height);
	//bool CheckHit2(int x, int y, int width, int height,int p);
	//void Stalker();

private:
	ColliderComponent* mCollider;
	Vector2* mPos;
	Vector2* mSize;
	const char* mFilename;
	Renderer* mRenderer;//�A�C�h����Ԃ̉摜
	bool mFall;
	bool mRight;//�E�ɐi��ł��邩�ǂ����H
	//���̐��l
	int old_x;//1�t���[���O�̂��ʒu
	int old_y;//1�t���[���O�̂��ʒu

	bool mStalker;//true�ŒǐՏ�Ԃ�
	Vector2 pPos;
	Vector2 direction;
	int staSize;//�ǐՔ͈�
	Renderer* sRenderer;//�ǐՏ�Ԃ̉摜
	Renderer* paralRenderer;//�}�q��Ԃ̉摜
	float speed;//�ǂ������鑬�x
	float paraTime;
	CountDownTimer* paralimitTime;
	bool paral;
	CountDownTimer* playerHitTimer;//�v���C���[�ƘA���œ�����Ȃ����߂̃^�C�}�[
	CountDownTimer* paralimitTimer;//�A���Ŗ�჏�ԂɂȂ�Ȃ����߂̃^�C�}�[

	Sound* sound;//��
	float atTime;
	CountDownTimer* attackTimer;//
	bool rush;
	Vector2 psPos;
	Vector2* mVelocity;
	Renderer* bomRenderer;

	CountUpTimer* mUpTimer;

	bool isRush;

	float moveTime;
	CountDownTimer* moveTimer;
	CountUpTimer* deathUpTimer;
};