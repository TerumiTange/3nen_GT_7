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
	bool RGoal();//�S�[���������ǂ���

private:
	int mHp;//�̗�
	int mMaxHp;//�ő�̗�
	float mInvincibleTime;//���G����
	bool mGoal;//�S�[���������ǂ���
	Vector2* mPos;//
	Vector2* mVelocity;//�x�N�g��
	float maxSpeed;//�ő呬�x
	float mAcceleration;//�����x
	Vector2* mSize;//�傫��
	const char* mFilename;//�摜��
	Renderer* mRenderer;//�`��֐�
	Renderer* mStaticElectricity;//�Ód�C�摜
	Input* mInput;//�L�[����
	CountDownTimer* mCountTimer;//�J�E���g�_�E���^�C�}�[
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