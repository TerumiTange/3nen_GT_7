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
	Renderer* mRenderer;//�A�C�h����Ԃ̉摜
	bool mFall;
	bool mRight;//�E�ɐi��ł��邩�ǂ���
	//���̐��l
	int old_x;//1�t���[���O�̈ʒu
	int old_y;//1�t���[���O�̈ʒu

	bool mStalker;//true�ŒǐՏ�Ԃ�
	Vector2 pPos;
	Vector2 direction;
	Vector2* staSize;//�ǐՂ͈̔�
	Renderer* sRenderer;//�ǐՏ�Ԃ̉摜
	//Renderer* paralRenderer//�}�q��Ԃ̉摜
	//float* speed;//�ǂ������鑬�x
};