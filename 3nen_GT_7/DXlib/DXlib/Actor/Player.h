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
	void Fall();//�d��
	void Move();//����
	void Movement();//�ړ��ʌv�Z
	void MovingFast();//�u�Ԉړ�
	virtual void Draw() override;//�`��
	void Damage();//�_���[�W�v�Z
	void Recovery();//��
	void SetPosition(const Vector2& position);//���̈ʒu���W�Ɉړ�������
	Vector2& GetPosition();//���݂̈ʒu���W��n��
	virtual void Hit(std::list<std::shared_ptr<Actor>> actors)override;//�����蔻��
	bool CheckHit(int x, int y, int width, int height);//�������Ă��邩�ǂ���
	bool CheckHitF(int x, int y, int width, int height);//�����ړ����ɓ������Ă��邩�ǂ���
	bool RGoal();//�S�[���������ǂ���
	bool GetMovingFast();//�u�Ԉړ������ǂ���

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
	float mGravity;//�d�͂̃X�s�[�h
	float mMovingFastGravity;//�����ړ����̏d��
	
	bool mMovingFast;//�����ړ����Ă邩�ǂ���
	int mMovingFastCount;//�����ړ��̃J�E���g
	int mMovingFastMaxCount;//�ő卂���ړ��̉�
	float mMovingFastTime;//�����ړ��񕜎���
	CountDownTimer* mMovingFastTimer;//�����ړ��񕜗p�^�C�}�[
	int mMovingFastAmount;//�����ړ��̈ړ���
	//Vector2* mMovingFastDifference;//�����ړ���̈ʒu�̍���
	float mMovingFastDifferenceX;//�����ړ���̈ʒu����X
	float mMovingFastDifferenceY;//�����ړ���̈ʒu����Y
	CountDownTimer* mNowMovingFastTimer;//�����ړ���Ԃ̃^�C�}�[
	float mNowMovingFastTime;//�����ړ���Ԃ̎���
	bool mNowMovingFast;//�����ړ������u��

	CountDownTimer* mFallTimer;//�d�͌y���̎��ԃ^�C�}�[
	float mFallTime;//�d�͌y���̎���

	//�u�Ԉړ��͈�苗���ړ�

	//bool mJump;//�W�����v���Ă��邩�ǂ���
	//bool mFloating;//���V���Ă��邩�ǂ���
	//int mElectricity;//���g�̓d�C�Q�[�W�̗�
	//bool mChargedState;//�ѓd��Ԃ��ǂ���
	//bool mPoppedState;//�͂�����Ԃ��ǂ���
	

	int old_x;//�����O��X���W
	int old_y;//�����O��Y���W
};