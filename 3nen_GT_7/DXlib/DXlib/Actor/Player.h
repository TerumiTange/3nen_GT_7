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
	virtual void Hit() override;
	bool GetMovingFast();//�u�Ԉړ������ǂ���

private:
	ColliderComponent* mCollider;
	int mHp;//�̗�
	int mMaxHp;//�ő�̗�
	float mInvincibleTime;//���G����
	Vector2* mPos;//�|�W�V����
	Vector2* mVelocity;//�x�N�g��
	float maxSpeed;//�ő呬�x
	float mAcceleration;//�����x
	Vector2* mSize;//�傫��
	const char* mFilename;//�摜��
	Renderer* mRenderer;//�`��֐�
	Renderer* mIdolRenderer;//�A�C�h����ԕ`��
	Renderer* mStaticElectricity;//�Ód�C�摜
	Renderer* mHeart;//�n�[�g�̉摜�iHP�j
	Renderer* mNumber;//�����ړ��񐔗p
	Input* mInput;//�L�[����
	CountDownTimer* mCountTimer;//�J�E���g�_�E���^�C�}�[
	bool mFall;//�����Ă��邩�ǂ���
	float mGravity;//�d�͂̃X�s�[�h
	float mMovingFastGravity;//�����ړ����̏d��
	
	bool mMovingFast;//�����ړ����Ă邩�ǂ���
	int mMovingFastCount;//�����ړ��̃J�E���g
	int mMovingFastMaxCount;//�ő卂���ړ��̉�

	int mMovingFastAmount;//�����ړ��̈ړ���
	CountDownTimer* mNowMovingFastTimer;//�����ړ���Ԃ̃^�C�}�[
	float mNowMovingFastTime;//�����ړ���Ԃ̎���
	bool mNowMovingFast;//�����ړ������u��

	bool mRight;//�E�������Ă��邩�ǂ���

	Sound* sound;

	Renderer* mContent;//�񐔂̒��g
	Renderer* mFrame;//�񐔂̎���
	CountUpTimer* mUpTimer;

	int old_x;//�����O��X���W
	int old_y;//�����O��Y���W
};