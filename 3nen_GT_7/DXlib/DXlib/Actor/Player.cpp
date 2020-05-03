#include "Player.h"
#include "../Device/WindowSize.h"
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
	mTeleportation(false),							  //�u�Ԉړ����Ă��邩�ǂ���
	mTeleportationCount(1),							  //�u�Ԉړ��ł����
	mTeleportationTime(0.5f),						  //�u�Ԉړ����񕜂���܂ł̎���
	mTeleportationTimer(new CountDownTimer()),		  //�u�Ԉړ��񕜗p�J�E���g�_�E���^�C�}�[
	mTeleportationAmount(200)						  //�u�Ԉړ��̈ړ���
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
	delete(mTeleportationTimer);
}

void Player::Update()
{
	//clsDx();
	printfDx("�̗�%d", mHp);
	printfDx("���G����%.001f", mCountTimer->Now());
	printfDx("�u�Ԉړ��ł����%d", mTeleportationCount);
	printfDx("�u�Ԉړ��ł���悤�ɂȂ�܂ł̎���%.01f", mTeleportationTimer->Now());

	mInput->JoyUpdate();//�W���C�p�b�h�X�V
	mCountTimer->Update();//���G���ԍX�V

	if (!mTeleportation)//�u�Ԉړ����łȂ����
	{
		mTeleportationTimer->Update();//�u�Ԉړ����ԍX�V
	}
	if ((mTeleportationCount <= 0) && (mTeleportationTimer->IsTime()))
	{
		mTeleportationCount = 1;
	}
	

	Actor::SetPos(*mPos);
	old_x = mPos->x;
	old_y = mPos->y;
	Fall();
	mFall = true;

	if (mInput->GetKeyDown(SPACE) || mInput->PadDown(Joy_A))
	{
		Teleportation();//�u�Ԉړ�
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
	if (mFall)
	{
		mPos->y += 16;
	}
}
void Player::Move()
{
	if (mTeleportation)return;//�u�Ԉړ����Ȃ烊�^�[��
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
	if (mTeleportation)
	{
		mVelocity->x = 0;
		mVelocity->y = 0;
		mTeleportation = false;
	}

	//��ʊO�ɏo���ꍇ�ʒu�C��
	if (mPos->x < 32)
	{
		mPos->x = 32;
	}
	if (mPos->x > ScreenWidth - 32)
	{
		mPos->x = ScreenWidth - 32;
	}
	if (mPos->y > ScreenHeight)
	{
		mPos->y = ScreenHeight;
	}
	if (mPos->y < 32)
	{
		mPos->y = 32;
	}
}

void Player::Teleportation()//�u�Ԉړ�
{
	if (mTeleportationCount <= 0)return;//0�ȉ��Ȃ烊�^�[��
	if (mTeleportation)return;//�u�Ԉړ����Ȃ烊�^�[��
	mTeleportation = true;
	mTeleportationCount--;
	
	if ((mInput->Horizontal() < 0) || (mInput->GetKey(A) || mInput->GetKey(LEFTARROW)))
	{
		mVelocity->x = -mTeleportationAmount;
	}
	else if ((mInput->Horizontal() > 0) || (mInput->GetKey(D) || mInput->GetKey(RIGHTARROW)))
	{
		mVelocity->x = mTeleportationAmount;
	}

	if (mInput->Vertical() < 0 || (mInput->GetKey(W) || mInput->GetKey(UPARROW)))
	{
		mVelocity->y = -mTeleportationAmount;
	}
	else if (mInput->Vertical() > 0 || (mInput->GetKey(S) || mInput->GetKey(DOWNARROW)))
	{
		mVelocity->y = mTeleportationAmount;
	}

	if (mVelocity->x == 0 && mVelocity->y == 0)//�������͂��Ȃ���ΉE�Ɉړ�
	{
		mVelocity->x = mTeleportationAmount;
	}

	mTeleportationTimer->SetTime(mTeleportationTime);
}

void Player::Damage()//�_���[�W
{
	if (mTeleportation)return;//�u�Ԉړ����Ȃ�
	if (mCountTimer->IsTime())
	{
		mHp--;
		mCountTimer->SetTime(mInvincibleTime);
	}

	if (mHp <= 0)
	{
		Destroy(this);
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

Vector2 & Player::GetPosition()
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
			if (CheckHit( a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
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
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
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

bool Player::RGoal()
{
	return mGoal;
}


