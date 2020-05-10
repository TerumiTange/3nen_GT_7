#include "Player.h"
#include "../Device/WindowSize.h"
#include "../Map/Map.h"
#include <algorithm>
#define NOMINMAX
#define max(a,b)            (((a) > (b)) ? (a) : (b))


Player::Player(const Vector2& position, const char* tag):
	Actor(tag),
	mMaxHp(4),										  //�ő�̗�
	mHp(4),											  //���݂̗̑�
	mInvincibleTime(4),								  //���G����
	mGoal(false),									  //�S�[���������ǂ���
	mPos(new Vector2(0,0)),							  //���݂̈ʒu
	mVelocity(new Vector2(0, 0)),					  //�ړ���
	maxSpeed(7),									  //�ő�X�s�[�h
	mAcceleration(0.5),								  //�����x
	mSize(new Vector2(64, 64)),						  //�����̑傫��
    mFilename(tag),									  //�摜��
	mRenderer(new Renderer(tag)),					  //�`��֐�
	mStaticElectricity(new Renderer("ThunderEffect")),//�Ód�C�̉摜
	mHeart(new Renderer("Metal")),					  //����HP��\������
	mInput(new Input()),							  //�L�[���͊֐�
	mCountTimer(new CountDownTimer()),				  //���G���ԍX�V�J�E���g�_�E���^�C�}�[
	mFall(true),									  //�����Ă��邩�ǂ���
	mGravity(16),									  //�d�͂̃X�s�[�h
	mMovingFastGravity(8),							  //�����ړ����̏d��
	mMovingFast(false),								  //�����ړ����Ă��邩�ǂ���
	mMovingFastCount(4),							  //�����ړ��ł����
	mMovingFastMaxCount(4),							  //�ő卂���ړ��̉�
	mMovingFastTime(0.5f),//0.5f					  //�����ړ����񕜂���܂ł̎���
	mMovingFastTimer(new CountDownTimer()),			  //�����ړ��񕜗p�J�E���g�_�E���^�C�}�[
	mMovingFastAmount(35),							  //�����ړ��̈ړ���
	mMovingFastDifferenceX(0),						  //�����ړ���̈ʒu�̍���X
	mMovingFastDifferenceY(0),						  //�����ړ���̈ʒu�̍���Y
	mNowMovingFastTimer(new CountDownTimer()),        //�����ړ���Ԃ̃^�C�}�[
	mNowMovingFastTime(0.2f),						  //�����ړ���Ԃ̎���
	mNowMovingFast(false),							  //�����ړ������u��
	mFallTimer(new CountDownTimer()),				  //�d�͌y���̎��ԃ^�C�}�[(IsTime()��false�Ȃ�y����)
	mFallTime(0.2f),								  //�d�͌y���̎���
	mNumber(new Renderer("Number"))
{
	mPos->x = position.x;
	mPos->y = position.y;
	Actor::SetPos(*mPos);   //�A�N�^�[�ɃZ�b�g
	Actor::SetSize(*mSize);	//�A�N�^�[�ɃZ�b�g
	mInput->Init();
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

	delete(mMovingFastTimer);
	delete(mNowMovingFastTimer);
	delete(mNumber);
	delete(mFallTimer);
}

void Player::Update()
{
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

	

	mInput->JoyUpdate();//�W���C�p�b�h�X�V
	mCountTimer->Update();//���G���ԍX�V

	if (!mMovingFast)//�����ړ����łȂ����
	{
		mMovingFastTimer->Update();//�����ړ��񕜎��ԍX�V
	}

	if ((mMovingFastCount <= 0) && (mMovingFastTimer->IsTime()))//�����ړ��񐔂������A�����ړ��񕜎��Ԃ��߂�����
	{
		mFall = true;
		//if (mMovingFast)return;
		//mMovingFastCount = 1;//�����ړ��񐔂�1�ɂ���
	}
	
	if (mNowMovingFastTimer->IsTime())//�����ړ������u�Ԃ̏������I��������
	{
		mMovingFast = false;
		mFall = true;
		mFallTimer->Update();
	}

	Actor::SetPos(*mPos);//���݂̈ʒu���W���A�N�^�[�ɃZ�b�g����
	old_x = mPos->x;//�ړ��O�Ɍ��݂̍��WX���X�V
	old_y = mPos->y;//�ړ��O�Ɍ��݂̍��WY���X�V
	Fall();//�d�͌v�Z
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

	Movement();//�ړ��v�Z
}
void Player::Fall()//�d��
{
	if (mMovingFast || !mFallTimer->IsTime())//�����ړ����܂��͏d�͌y�����Ȃ�
	{
		mPos->y += mMovingFastGravity;
		return;
	}
	if (!mFall)return;//�n�ʂɒ��n���Ă��Ȃ���΃��^�[��
	mPos->y += mGravity;
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

		//mMovingFastDifference->x -= mPos->x;
		//mMovingFastDifference->y -= mPos->y;
		mMovingFastDifferenceX -= mPos->x;//�����ړ��O�Ƃ̍������v�Z
		mMovingFastDifferenceY -= mPos->y;//�����ړ��O�Ƃ̍������v�Z
		mNowMovingFast = false;
		mNowMovingFastTimer->SetTime(mFallTime);//�d�͔����܂Ōy��
	}
	//��ʊO�ɏo���ꍇ�ʒu�C��
	if (mPos->x < 32)
	{
		mPos->x = 32;
	}
	if (mPos->x > Map::width * 32 - 32)
	{
		mPos->x = Map::width * 32 - 32;
	}
	//����ŏC��
	if (mPos->y < 32)
	{
		mPos->y = 32;
	}
	if (mPos->y > Map::height * 32 - 32)
	{
		mPos->y = Map::height * 32 - 32;
	}
	
}

void Player::MovingFast()//�u�Ԉړ�
{
	if (mMovingFastCount <= 0)return;//0�ȉ��Ȃ烊�^�[��
	if (mMovingFast)return;//�u�Ԉړ����Ȃ烊�^�[��
	if (!mNowMovingFastTimer->IsTime())return;//��莞�Ԃ��܂Ŗ���
	mMovingFast = true;
	mFall = false;
	mNowMovingFast = true;
	mMovingFastCount--;
	//mMovingFastDifference = mPos;
	mMovingFastDifferenceX = mPos->x;//�����ړ��O�̍��WX
	mMovingFastDifferenceY = mPos->y;//�����ړ��O�̍��WY

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

	mMovingFastTimer->SetTime(mMovingFastTime);//�񐔂��񕜂�����܂ł̎���
	mNowMovingFastTimer->SetTime(mNowMovingFastTime);//�����ɕK�v�Ȏ���
}

void Player::Damage()//�_���[�W
{
	if (mMovingFast)return;//�u�Ԉړ����Ȃ�
	if (mCountTimer->IsTime())//���G���ԂłȂ��Ȃ�
	{
		mHp--;//1�_���[�W�󂯂�
		mCountTimer->SetTime(mInvincibleTime);//���G���Ԃ��Z�b�g
	}

	if (mHp <= 0)//�̗͂��Ȃ��Ȃ�����
	{
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
	//mRenderer->Draw(*mPos);
	mRenderer->DrawE(*mPos, 64);
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
	DrawString(0, 0, "�u�Ԉړ��ł����:", GetColor(255, 0, 0));
	mNumber->DrawIntegerNumber(Vector2(150, 0), mMovingFastCount);
}

void Player::SetPosition(const Vector2& position)
{
	*mPos = position;
}

Vector2& Player::GetPosition()
{
	return *mPos;
}

void Player::Hit(std::list<std::shared_ptr<Actor>> actors)
{
	for (auto& a : actors)
	{
		if (a->Tag() == "DeathBlock")
		{
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				Actor::Destroy(this);
			}
		}
		if (a->Tag() == "Wall")
		{
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				//if (mMovingFast)
				//{
				//	mMovingFastCount = 4;
				//}
				mMovingFastCount = 4;

				if (old_y + mSize->y <= a->Position()->y)//�����̉��ɓ��������Ƃ�
				{
					mPos->y = a->Position()->y - mSize->y;
					mFall = false;
				}
				else if (old_y > a->Position()->y + a->Size()->y)//�����̏�ɓ��������Ƃ�
				{
					mPos->y = a->Position()->y + a->Size()->y;
					if (mVelocity->y < 0)
					{
						mVelocity->y = 0;
					}
				}
				else if (old_x >= a->Position()->x + a->Size()->x)//�����̍��ɓ��������Ƃ�
				{
					mPos->x = a->Position()->x + a->Size()->x + 1;
					if (mVelocity->x < 0)
					{
						mVelocity->x = 0;
					}
				}

				else if (old_x + mSize->x <= a->Position()->x)//�����̉E�ɓ��������Ƃ�
				{
					mPos->x = a->Position()->x - mSize->x - 1;
					if (mVelocity->x < 0)
					{
						mVelocity = 0;
					}
				}

				

				//mPos->x = old_x;
			}
		}

		if (a->Tag() == "Floor")
		{
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				mFall = false;//�d�͂��������Ă��Ȃ�
				mPos->y = a->Position()->y - mSize->y;
				mMovingFastCount = 4;
			}
		}
		if (a->Tag() == "Goal")
		{
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				mGoal = true;
			}
		}
		if (a->Tag() == "SmallEnemy")
		{
			//if (mMovingFast)//�����ړ����ł����
			//{
			//	if (CheckHitF(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			//	{
			//		if (a->GetElectricShock())Destroy(a);
			//		a->SetElectricShock(true);
			//		mMovingFastCount++;
			//	}
			//}
			//else if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			//{
			//	Damage();
			//}
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				if (a->GetElectricShock())Destroy(a);
				if (mNowMovingFast)
				{
					a->SetElectricShock(true);
					mMovingFastCount++;
				}
				Damage();
			}
		}

		if (a->Tag() == "FlyEnemy")
		{
			//if (mMovingFast)//�����ړ����ł����
			//{
			//	if (CheckHitF(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			//	{
			//		if (a->GetElectricShock())Destroy(a);
			//		a->SetElectricShock(true);
			//		mMovingFastCount++;
			//	}
			//}
			//else if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			//{
			//	Damage();
			//}
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				if (mNowMovingFast)
				{
					a->SetElectricShock(true);
					//mMovingFastCount++;
					mMovingFastCount = 4;
				}
				Damage();
			}
		}
	}
}


bool Player::CheckHit(int x, int y, int width, int height)
{
	//int L1 = mPos->x;
	//int R1 = mPos->x + mSize->x;
	//int L2 = x;
	//int R2 = x + width;
	//if (R1 < L2)return false;
	//if (R2 < L1)return false;
	if (mPos->x + mSize->x < x)return false;
	if (x + width < mPos->x)return false;

	//int U1 = mPos->y;
	//int D1 = mPos->y + mSize->y;
	//int U2 = y;
	//int D2 = y + height;
	//if (D1 < U2)return false;
	//if (D2 < U1)return false;
	if (mPos->y + mSize->y < y)return false;
	if (y + height < mPos->y)return false;
	return true;
}

bool Player::CheckHitF(int x, int y, int width, int height)
{
	//if (mPos->x + mSize->x < x)return false;
	//if (x + width < mPos->x - mMovingFastDifference.x) return false;
	//if (mPos->y + mSize->y < y)return false;
	//if (y + height < mPos->y - mMovingFastDifference.y)return false;

	if (mPos->x + mSize->x < x)return false;
	if (mPos->x - mMovingFastDifferenceX > x + width)return false;
	if (mPos->y > y + height)return false;
	if (y > mPos->y + mSize->y + mMovingFastDifferenceY)return false;
	return true;
}

bool Player::RGoal()
{
	return mGoal;
}

bool Player::GetMovingFast()
{
	return mMovingFast;
}


