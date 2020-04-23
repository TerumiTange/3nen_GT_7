#pragma once
#include "Actor.h"
#include "../System/Input.h"
#include "../Utility/Vector2.h"
#include "../Device/Renderer.h"

class Player:
	public Actor
{
public :
	Player(const char* tag = "Player");
	Player(const Vector2& position, const char* tag = "Player");
	~Player();
	virtual void End()override;
	void Init();
	virtual void Update()override;
	virtual void Draw() override;
	void SetPosition(const Vector2& position);
	Vector2& GetPosition();
	virtual void Hit(std::list<std::shared_ptr<Actor>> actors)override;
	bool CheckHit(int x, int y, int width, int height);
	//void HitEnemy();

private:
	Vector2* mPos;
	Vector2* old_mPos;//�ړ��O�̈ʒu
	Vector2* mVelocity;//�x�N�g��
	Vector2* mSize;
	const char* mFilename;
	Renderer* mRenderer;
	Input* mInput;
	bool mFall;//�����Ă��邩�ǂ���
	bool mJump;//�W�����v���Ă��邩�ǂ���
	bool mFloating;//���V���Ă��邩�ǂ���
	int mElectricity;//���g�̓d�C�Q�[�W�̗�
	bool mChargedState;//�ѓd��Ԃ��ǂ���
	bool mPoppedState;//�͂�����Ԃ��ǂ���
	/*
	�ړ����邱�Ƃœd�C�Q�[�W�����܂�
	�����ɐG���Ɠd�C�Q�[�W��0�ɂ��āA�͂�����ԂɂȂ�
	�͂�����Ԃ��Ɣ��Ε����ɔ��ł����i���j
	�d�C�Q�[�W��100�ɂȂ��Ă���10�b���Ƒѓd��ԂɂȂ�-���{���͋����ɋ߂Â��Ɣ���
	�ѓd��Ԃ��ƈ�x�������̃A�N�V������2�{�ɂȂ�
	�Ƃ肠����
	*/
	int old_x;
	int old_y;
};