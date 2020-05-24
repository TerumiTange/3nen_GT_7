#include "Player.h"
#include "../Device/WindowSize.h"
#include "../Map/Map.h"
#include "ActorManager.h"
#include <algorithm>
#define NOMINMAX
#define max(a,b)            (((a) > (b)) ? (a) : (b))


Player::Player(const Vector2& position, const char* tag) :
	Actor(tag),
	mCollider(new ColliderComponent(this)),
	mMaxHp(4),										  //�ő�̗�
	mHp(4),											  //���݂̗̑�
	mInvincibleTime(4),								  //���G����
	mPos(new Vector2(0, 0)),							  //���݂̈ʒu
	mVelocity(new Vector2(0, 0)),					  //�ړ���
	maxSpeed(7),									  //�ő�X�s�[�h
	mAcceleration(0.5),								  //�����x
	mSize(new Vector2(32, 32)), 						  //�����̑傫��
    mFilename(tag),									  //�摜��
	mRenderer(new Renderer(tag)),					  //�`��֐�
	mStaticElectricity(new Renderer("ThunderEffect")),//�Ód�C�̉摜
	mHeart(new Renderer("Metal")),					  //����HP��\������
	mInput(new Input()),							  //�L�[���͊֐�
	mCountTimer(new CountDownTimer()),				  //���G���ԍX�V�J�E���g�_�E���^�C�}�[
	mFall(true),									  //�����Ă��邩�ǂ���
	mGravity(5),									  //�d�͂̃X�s�[�h
	mMovingFastGravity(1),							  //�����ړ����̏d��
	mMovingFast(false),								  //�����ړ����Ă��邩�ǂ���
	mMovingFastCount(4),							  //�����ړ��ł����
	mMovingFastMaxCount(4),							  //�ő卂���ړ��̉񐔁[
	mMovingFastAmount(25),							  //�����ړ��̈ړ���
	mNowMovingFastTimer(new CountDownTimer()),        //�����ړ���Ԃ̃^�C�}�[
	mNowMovingFastTime(0.2f),						  //�����ړ���Ԃ̎���
	mNowMovingFast(false),							  //�����ړ������u��
	mNumber(new Renderer("Number")),
	sound(new Sound()),
	mContent(new Renderer("content")),
	mFrame(new Renderer("frame"))
{
	mPos->x = position.x;
	mPos->y = position.y;
	Actor::SetPos(*mPos);   //�A�N�^�[�ɃZ�b�g
	Actor::SetSize(*mSize);	//�A�N�^�[�ɃZ�b�g
	mInput->Init();
	sound->Init();
	sound->Load("./Assets/Sound/damage.wav");//�_���[�W
	sound->Load("./Assets/Sound/pdeth.wav");//���S
	sound->Load("./Assets/Sound/movingfast.wav");//�����ړ�
	sound->Load("./Assets/Sound/crash.wav");//�ǂƂ̏Փ�
}

Player::~Player() = default;

void Player::End()//�������̊J��
{
	delete(mPos);
	delete(mVelocity);
	delete(mSize);
	delete(mRenderer);
	delete(mStaticElectricity);
	delete(mHeart);
	delete(mInput);
	delete(mCountTimer);

	delete(mNowMovingFastTimer);
	delete(mNumber);
	delete(sound);
	delete(mContent);
	delete(mFrame);
}

void Player::Update()
{
	mElectricTimer->Update();//�G�̖�თp

	if (mMovingFastCount > mMovingFastMaxCount)//�ő�񐔂��I�[�o�[������
	{
		mMovingFastCount = mMovingFastMaxCount;//�ő�񐔂ɂ���
	}
	//clsDx();
	//�f�o�b�O�p
	//printfDx("�̗�%d", mHp);
	//printfDx("���G����%.001f", mCountTimer->Now());
	//printfDx("�u�Ԉړ��ł����%d", mMovingFastCount);
	//printfDx("�u�Ԉړ��ł���悤�ɂȂ�܂ł̎���%.01f", mMovingFastTimer->Now());

	if (mHp <= 0)return;//�̗͂��Ȃ��Ȃ����瑀�삵�Ȃ��悤�ɂ���

	if (mInput->GetKeyDown(K))
	{
		Damage();
	}

	mInput->JoyUpdate();//�W���C�p�b�h�X�V
	mCountTimer->Update();//���G���ԍX�V

	if (mNowMovingFastTimer->IsTime())//�����ړ������u�Ԃ̏������I��������
	{
		mMovingFast = false;
		//mFall = true;
	}

	Actor::SetPos(*mPos);//���݂̈ʒu���W���A�N�^�[�ɃZ�b�g����
	old_x = mPos->x;//�ړ��O�Ɍ��݂̍��WX���X�V
	old_y = mPos->y;//�ړ��O�Ɍ��݂̍��WY���X�V
	mNowMovingFastTimer->Update();//�����ړ������u�Ԃ̏������X�V
	

	if (mInput->GetKeyDown(SPACE) || mInput->PadDown(Joy_A))//�X�y�[�X�܂��̓R���g���[���[��A����������
	{
		MovingFast();//�u�Ԉړ�
	}

	if (mInput->GetKeyDown(H))//�f�o�b�O�p
	{
		Recovery();//�̗͉�
	}

	Move();//�ړ�����
	Fall();//�d�͌v�Z
	Movement();//�ړ��v�Z
}
void Player::Fall()//�d��
{
	if (mMovingFast)//�����ړ����Ȃ�
	{
		//mPos->y += mMovingFastGravity;//�y���d��
		mVelocity->y += mMovingFastGravity;
		return;
	}
	if (!mFall)return;//�n�ʂɒ��n���Ă��Ȃ���΃��^�[��
	//mPos->y += mGravity;
	mVelocity->y += mGravity;
}

void Player::Move()
{
	if (mMovingFast)return;//�u�Ԉړ����Ȃ烊�^�[��
	if ((mInput->Horizontal() < 0) || (mInput->GetKey(A) || mInput->GetKey(LEFTARROW)))//���ړ�
	{
		mVelocity->x = min(mVelocity->x - mAcceleration, -maxSpeed);
	}
	else if ((mInput->Horizontal() > 0) || (mInput->GetKey(D) || mInput->GetKey(RIGHTARROW)))//�E�ړ�
	{
		mVelocity->x = max(mVelocity->x + mAcceleration, maxSpeed);
	}
}

void Player::Movement()//�ړ�����
{
	mPos->y += mVelocity->y;//�ړ�����Y
	mPos->x += mVelocity->x;//�ړ�����X


	if (!mNowMovingFast)
	{
		mVelocity->y *= 0.7f;//�����Ŋ��������o��
		mVelocity->x *= 0.9f;//�����Ŋ��������o��
	}
	
	if (mNowMovingFast&&mNowMovingFastTimer->IsTime())//�����ړ��Ȃ犵��0
	{
		mVelocity->x = 0;
		mVelocity->y = 0;

		mNowMovingFast = false;
	}
	//��ʊO�ɏo���ꍇ�ʒu�C��
	if (mPos->x < 32)
	{
		mPos->x = 32;
	}
	if (mPos->x > Map::width * 32 - 64)
	{
		mPos->x = Map::width * 32 - 64;
	}
	if (mPos->y < 33)
	{
		mPos->y = 33;
	}
	if (mPos->y > Map::height * 32 - 64)
	{
		mPos->y = Map::height * 32 - 64;
	}
	
}

void Player::MovingFast()//�u�Ԉړ�
{
	if (mMovingFastCount <= 0)return;//�񐔂�0�ȉ��Ȃ烊�^�[��
	//if (mMovingFast)return;//�u�Ԉړ����Ȃ烊�^�[��
	if (!mNowMovingFastTimer->IsTime())return;//��莞�Ԃ��܂Ŗ���
	sound->PlaySE("./Assets/Sound/movingfast.wav");
	mMovingFast = true;
	mFall = false;
	mNowMovingFast = true;
	mMovingFastCount--;

	mVelocity->x = mInput->Horizontal()*mMovingFastAmount;//�R���g���[���ł̈ړ�
	mVelocity->y = mInput->Vertical()*mMovingFastAmount;  //�R���g���[���ł̈ړ�

	//�L�[�{�[�h�ł̈ړ�
	if (mInput->GetKeyDown(LEFTARROW) || mInput->GetKeyDown(A))
	{
		mVelocity->x = -mMovingFastAmount;
	}
	else if (mInput->GetKeyDown(D) || mInput->GetKeyDown(RIGHTARROW))
	{
		mVelocity->x = mMovingFastAmount;
	}

	if (mInput->GetKeyDown(W) || mInput->GetKeyDown(UPARROW))
	{
		mVelocity->y = -mMovingFastAmount;
	}
	else if (mInput->GetKeyDown(S) || mInput->GetKeyDown(DOWNARROW))
	{
		mVelocity->y = mMovingFastAmount;
	}


	if (mVelocity->x == 0 && mVelocity->y == 0)//�������͂��Ȃ���ΉE�Ɉړ�
	{
		mVelocity->x = mMovingFastAmount;
	}


	mNowMovingFastTimer->SetTime(mNowMovingFastTime);//�����ɕK�v�Ȏ���
}

void Player::Damage()//�_���[�W
{
	if (mMovingFast)return;//�u�Ԉړ����Ȃ�
	if (mCountTimer->IsTime())//���G���ԂłȂ��Ȃ�
	{
		mHp--;//1�_���[�W�󂯂�
		sound->PlaySE("./Assets/Sound/damage.wav");
		mCountTimer->SetTime(mInvincibleTime);//���G���Ԃ��Z�b�g
	}

	if (mHp <= 0)//�̗͂��Ȃ��Ȃ�����
	{
		sound->PlaySEF("./Assets/Sound/pdeth.wav");
		Destroy(this, 3.f);//3�b��Ɏ��S
	}
}

void Player::Recovery()//�̗͉�
{
	mHp++;
	if (mMaxHp < mHp)//�ő�̗͂𒴂�����
	{
		mHp = mMaxHp;//�ő�̗͂ɂ���
	}
}


void Player::Draw()//�`��
{
	mRenderer->Draw(*mPos);
	//mRenderer->DrawE(*mPos, 64);
	if (mNowMovingFast)
	{
		mStaticElectricity->Draw(mPos->x - 16, mPos->y + 32);
	}
	for (size_t i = 0; i < mHp; ++i)
	{
		mHeart->Drawb(10 + i * 36, 36);
	}
    //DrawString(0, 0, "", mMovingFastCount);
	//DrawFormatString(10, 0, GetColor(255, 0, 0), "�u�Ԉړ��ł����%d", mMovingFastCount);
	//SetFontSize(32);
	//DrawString(0, 0, "�u�Ԉړ��ł����:", GetColor(255, 0, 0));
	//mNumber->DrawIntegerNumber(Vector2(350, 0), mMovingFastCount);

	for (int i = 0; i < mMovingFastMaxCount; ++i)
	{
		mFrame->Drawb(i * 32, 0);
	}
	for (int i = 0; i < mMovingFastCount; ++i)
	{
		mContent->Drawb(i * 32, 0);
	}
}

void Player::SetPosition(const Vector2& position)
{
	*mPos = position;
}

Vector2& Player::GetPosition()
{
	return *mPos;
}

void Player::Hit()
{
	if (mCollider->onCollisionStay().empty() && mCollider->onCollisionEnter().empty())//���Ƃ��������Ă��Ȃ����
	{
		mFall = true;
		return;
	}

	for (auto && hit : mCollider->onCollisionStay())//�A���œ������Ă���Ƃ�
	{
		if (hit->getOwner()->Tag() == "Wall")
		{
			mMovingFastCount = 4;
			auto cPosX = hit->getOwner()->Position()->x;
			auto cPosY = hit->getOwner()->Position()->y;
			auto cSizeX = hit->getOwner()->Size()->x;
			auto cSizeY = hit->getOwner()->Size()->y;

			//if (mPos->y + mSize->y > cPosY)//�����̉��ɂ������Ă���
			//{
			//	mPos->y = cPosY - mSize->y;
			//	mVelocity->y = 0;
			//	mFall = false;
			//}
			//if (mPos->y <= cPosY + cSizeY && old_y > cPosY + cSizeY)//�����̏�ɓ��������Ƃ�
			//{
			//	mPos->y = cPosY + mSize->y + 1;
			//	mVelocity->y = 0;
			//}
			if (old_y < cPosY)//��������
			{
				if (mVelocity->y > 0)
				{
					mPos->y = cPosY - mSize->y;
					mFall = false;
				}
			}
			else if (old_y > cPosY)//����������
			{
				mPos->y = cPosY + cSizeY + 1;
			}
			else if (old_x < cPosX)//��������
			{
				mPos->x = cPosX - mSize->x;
				mVelocity->x = 0;
			}
			else if (old_x > cPosX)//�������E
			{
				mPos->x = cPosX + mSize->x;
				mVelocity->x = 0;
			}
		}
	}

	for (auto && hit : mCollider->onCollisionEnter())//���������u��
	{
		auto cPosX = hit->getOwner()->Position()->x;
		auto cPosY = hit->getOwner()->Position()->y;
		auto cSizeX = hit->getOwner()->Size()->x;
		auto cSizeY = hit->getOwner()->Size()->y;
		if (hit->getOwner()->Tag() == "Wall")
		{
			mMovingFastCount = 4;
			if (old_y < cPosY)//��������
			{
				mPos->y = cPosY - mSize->y;
				mFall = false;
			}
			else if (old_y > cPosY)//��������
			{
				mPos->y = cPosY + cSizeY;
				mVelocity->y = 0;
			}
			else if (old_x < cPosX)//��������
			{
				mPos->x = cPosX - mSize->x;
				mVelocity->x = 0;
			}
			else if (old_x > cPosX)//�������E
			{
				mPos->x = cPosX + mSize->x + 1;
				mVelocity->x = 0;
			}
			//mPos->x = old_x;
			//mPos->y = old_y;
			//if (mPos->y + mSize->y >= cPosY)//�����̉��ɂ�������
			//{
			//	mPos->y = cPosY - mSize->y;
			//	mFall = false;
			//
			//}
			//if (mPos->y <= cPosY + cSizeY && old_y > cPosY + cSizeY)//�����̏�ɓ��������Ƃ�
			//{
			//	mPos->y = cPosY + mSize->y + 1;
			//	mVelocity->y = 0;
			//}
			//if (mPos->y + mSize->y >= cPosY)//�����̉��ɓ��������Ƃ�
			//{
			//	mPos->y = cPosY - cSizeY;
			//	mFall = false;
			//}
			//if (mPos->y <= cPosY + cSizeY)//�����̏�ɓ��������Ƃ�
			//{
			//	sound->PlaySEF("./Assets/Sound/crash.wav");
			//	mPos->y = cPosY + cSizeY;
			//	if (mVelocity->y < 0)
			//	{
			//		mVelocity->y = 0;
			//	}
			//}
			//else if (old_x >= cPosX + cSizeX)//�����̍��ɓ��������Ƃ�
			//{
			//	sound->PlaySEF("./Assets/Sound/crash.wav");
			//	mPos->x = cPosX + cSizeX + 1;
			//	if (mVelocity->x < 0)
			//	{
			//		mVelocity->x = 0;
			//	}
			//
			//}
			//else if (old_x + mSize->x <= cPosX)//�����̉E�ɓ��������Ƃ�
			//{
			//	sound->PlaySEF("./Assets/Sound/crash.wav");
			//	mPos->x = cPosX - mSize->x - 1;
			//	if (mVelocity->x > 0)
			//	{
			//		mVelocity->x = 0;
			//	}
			//}
		
		}
		/*
		if (hit->getOwner()->Tag() == "FlyEnemy")
		{
			if (mMovingFast)//�����ړ���ԂȂ��
			{
				if (hit->getOwner()->GetElectricShock())Destroy(hit->getOwner());
				hit->getOwner()->SetElectricShock(true);
				mMovingFastCount++;
			}
			if (mNowMovingFast)//�����ړ���ԏ���������ԂȂ��
			{
				hit->getOwner()->SetElectricShock(true);
				mMovingFastCount = 4;
			}

			if (!hit->getOwner()->GetElectricShock())
			{
				Damage();
			}
		}
		*/
	}
}

bool Player::GetMovingFast()
{
	return mMovingFast;
}


