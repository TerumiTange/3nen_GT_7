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
	mInput(new Input()),							  //�L�[���͊֐�
	mCountTimer(new CountDownTimer()),				  //���G���ԍX�V�J�E���g�_�E���^�C�}�[
	mFall(true),									  //�����Ă��邩�ǂ���
	mGravity(16),									  //�d�͂̃X�s�[�h
	mMovingFastGravity(8),							  //�����ړ����̏d��
	mMovingFast(false),								  //�����ړ����Ă��邩�ǂ���
	mMovingFastCount(1),							  //�����ړ��ł����
	mMovingFastMaxCount(1),							  //�ő卂���ړ��̉�
	mMovingFastTime(0.5f),//0.5f					  //�����ړ����񕜂���܂ł̎���
	mMovingFastTimer(new CountDownTimer()),			  //�����ړ��񕜗p�J�E���g�_�E���^�C�}�[
	mMovingFastAmount(200),							  //�����ړ��̈ړ���
	//mMovingFastDifference(new Vector2(0,0)),		  //�����ړ���̈ʒu�̍���
	mMovingFastDifferenceX(0),						  //�����ړ���̈ʒu�̍���X
	mMovingFastDifferenceY(0),						  //�����ړ���̈ʒu�̍���Y
	mNowMovingFastTimer(new CountDownTimer()),        //�����ړ���Ԃ̃^�C�}�[
	mNowMovingFast(false)							  //�����ړ������u��
{
	mPos->x = position.x;
	mPos->y = position.y;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
	mInput->Init();
}

Player::~Player() = default;

void Player::End()
{
	delete(mPos);
	delete(mVelocity);
	delete(mSize);
	delete(mRenderer);
	delete(mStaticElectricity);
	delete(mInput);
	delete(mCountTimer);

	//delete(mMovingFastDifference);

	delete(mMovingFastTimer);
	delete(mNowMovingFastTimer);
	
	
}

void Player::Update()
{
	if (mMovingFastCount > mMovingFastMaxCount)//�ő�񐔂��I�[�o�[������
	{
		mMovingFastCount = mMovingFastMaxCount;
	}
	//clsDx();
	printfDx("�̗�%d", mHp);
	printfDx("���G����%.001f", mCountTimer->Now());
	printfDx("�u�Ԉړ��ł����%d", mMovingFastCount);
	printfDx("�u�Ԉړ��ł���悤�ɂȂ�܂ł̎���%.01f", mMovingFastTimer->Now());
	//printfDx("x�̒l%.1f", mMovingFastDifferenceX);
	//printfDx("y�̒l%.1f", mMovingFastDifferenceY);

	if (mHp <= 0)return;

	

	mInput->JoyUpdate();//�W���C�p�b�h�X�V
	mCountTimer->Update();//���G���ԍX�V

	if (!mMovingFast)//�u�Ԉړ����łȂ����
	{
		mMovingFastTimer->Update();//�u�Ԉړ����ԍX�V
	}
	if ((mMovingFastCount <= 0) && (mMovingFastTimer->IsTime()))
	{
		mFall = true;
		//if (mMovingFast)return;
		mMovingFastCount = 1;
	}
	
	if (mNowMovingFastTimer->IsTime())
	{
		mMovingFast = false;
		mFall = true;
	}

	Actor::SetPos(*mPos);
	old_x = mPos->x;
	old_y = mPos->y;
	Fall();
	mNowMovingFastTimer->Update();
	

	if (mInput->GetKeyDown(SPACE) || mInput->PadDown(Joy_A))
	{
		MovingFast();//�u�Ԉړ�
	}

	if (mInput->GetKeyDown(H))
	{
		Recovery();
	}

	Move();

	Movement();
}
void Player::Fall()//�d��
{
	if (mMovingFast)
	{
		mPos->y += mMovingFastGravity;
		return;
	}
	if (!mFall)return;
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
	mPos->y += mVelocity->y;
	mVelocity->y *= 0.7f;
	mPos->x += mVelocity->x;//�ړ�����
	mVelocity->x *= 0.9f;//�����Ŋ��������o��
	
	if (mNowMovingFast)//�����ړ��Ȃ犵��0
	{
		mVelocity->x = 0;
		mVelocity->y = 0;
		
		//mMovingFastDifference->x -= mPos->x;
		//mMovingFastDifference->y -= mPos->y;
		mMovingFastDifferenceX -= mPos->x;
		mMovingFastDifferenceY -= mPos->y;
		mNowMovingFast = false;
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
	if (mPos->y > ScreenHeight)
	{
		mPos->y = ScreenHeight;
	}
	if (mPos->y < Map::height * 32 - ScreenHeight - 32)
	{
		mPos->y = Map::height * 32 - ScreenHeight - 32;
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
	mMovingFastDifferenceX = mPos->x;
	mMovingFastDifferenceY = mPos->y;

	if ((mInput->Horizontal() < 0) || (mInput->GetKey(A) || mInput->GetKey(LEFTARROW)))
	{
		mVelocity->x = -mMovingFastAmount;
	}
	else if ((mInput->Horizontal() > 0) || (mInput->GetKey(D) || mInput->GetKey(RIGHTARROW)))
	{
		mVelocity->x = mMovingFastAmount;
	}

	if (mInput->Vertical() < 0 || (mInput->GetKey(W) || mInput->GetKey(UPARROW)))
	{
		mVelocity->y = -mMovingFastAmount;
	}
	else if (mInput->Vertical() > 0 || (mInput->GetKey(S) || mInput->GetKey(DOWNARROW)))
	{
		mVelocity->y = mMovingFastAmount;
	}

	mVelocity->x = mInput->Horizontal()*mMovingFastAmount;
	mVelocity->y = mInput->Vertical()*mMovingFastAmount;

	if (mVelocity->x == 0 && mVelocity->y == 0)//�������͂��Ȃ���ΉE�Ɉړ�
	{
		mVelocity->x = mMovingFastAmount;
	}

	mMovingFastTimer->SetTime(mMovingFastTime);
	mNowMovingFastTimer->SetTime(0.2f);
}

void Player::Damage()//�_���[�W
{
	if (mMovingFast)return;//�u�Ԉړ����Ȃ�
	if (mCountTimer->IsTime())
	{
		mHp--;
		mCountTimer->SetTime(mInvincibleTime);
	}

	if (mHp <= 0)
	{
		Destroy(this, 3.f);//3�b��Ɏ��S
	}
}

void Player::Recovery()//�̗͉�
{
	mHp++;
	if (mMaxHp < mHp)
	{
		mHp = mMaxHp;
	}
}


void Player::Draw()
{
	mRenderer->Draw(*mPos);
	//if (mPoppedState)
	//{
	//	mStaticElectricity->Draw(mPos->x - 16, mPos->y + 32);
	//}
	//test�p
	//int a;
	//a = LoadGraph("./Assets/Texture/Player.png");
	//DrawGraph(mPos->x, mPos->y, a, TRUE);
	//DeleteGraph(a);
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
				mPos->x = old_x;

			}
		}

		if (a->Tag() == "Floor")
		{
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				mFall = false;//�d�͂��������Ă��Ȃ�
				mPos->y = a->Position()->y - mSize->y;
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
			if (mMovingFast)//�����ړ����ł����
			{
				if (CheckHitF(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
				{
					if (a->GetElectricShock())Destroy(a);
					a->SetElectricShock(true);
					mMovingFastCount++;
				}
			}
			else if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				Damage();
			}
		}

		if (a->Tag() == "FlyEnemy")
		{
			if (mMovingFast)//�����ړ����ł����
			{
				if (CheckHitF(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
				{
					if (a->GetElectricShock())Destroy(a);
					a->SetElectricShock(true);
					mMovingFastCount++;
				}
			}
			else if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
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


