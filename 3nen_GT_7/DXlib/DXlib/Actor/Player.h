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
	virtual void Update()override;//�X�V
	void Fall();
	void Move();
	void Movement();//�ړ��ʌv�Z
	void Teleportation();//�u�Ԉړ�
	virtual void Draw() override;
	void Damage();//�_���[�W�v�Z
	void Recovery();//��
	void SetPosition(const Vector2& position);
	Vector2& GetPosition();
	virtual void Hit(std::list<std::shared_ptr<Actor>> actors)override;
	bool CheckHit(int x, int y, int width, int height);//�������Ă��邩�ǂ���
	bool RGoal();//�S�[���������ǂ���

private:
	int mHp;//�̗�
	int mMaxHp;//�ő�̗�
	float mInvincibleTime;//���G����
	bool mGoal;//�S�[���������ǂ���
	Vector2* mPos;//�|�W�V����
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
	
	bool mTeleportation;//�u�Ԉړ����Ă邩�ǂ���
	int mTeleportationCount;//�u�Ԉړ��̃J�E���g
	float mTeleportationTime;//�u�Ԉړ��񕜎���
	CountDownTimer* mTeleportationTimer;//�u�Ԉړ��񕜗p�^�C�}�[
	int mTeleportationAmount;//�u�Ԉړ��̈ړ���

	//�u�Ԉړ��͈�苗���ړ�

	//bool mJump;//�W�����v���Ă��邩�ǂ���
	//bool mFloating;//���V���Ă��邩�ǂ���
	//int mElectricity;//���g�̓d�C�Q�[�W�̗�
	//bool mChargedState;//�ѓd��Ԃ��ǂ���
	//bool mPoppedState;//�͂�����Ԃ��ǂ���
	

	int old_x;
	int old_y;
};