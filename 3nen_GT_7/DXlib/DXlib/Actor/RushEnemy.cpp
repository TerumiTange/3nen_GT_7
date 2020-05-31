#include "RushEnemy.h"
#include "ActorManager.h"
#include "Player.h"
#include "../Collider//ComponentManager.h"

RushEnemy::RushEnemy(const Vector2 & pos, const char * tag) :
	Actor(tag),
	mCollider(new ColliderComponent(this)),
	mPos(new Vector2(0, 0)),//�|�W�V����
	mSize(new Vector2(32, 32)),//�T�C�Y
	mFilename(tag),//
	mRenderer(new Renderer("Enemy3")),//�A�C�h����Ԃ̉摜
	mFall(false),//�d��
	mRight(true),
	mStalker(false),//�ǐՏ�Ԃ��H
	staSize(200),//�ǐՔ͈�
	sRenderer(new Renderer("Enemy3")),//�ǐՏ�Ԃ̉摜
	paralRenderer(new Renderer("ThunderEffect")),//�}�q��Ԃ̉摜
	speed(250.0f),//���x
	paraTime(4.0f),//�}�q����
	paralimitTime(new CountDownTimer()),//�}�q���Ԃ̃^�C�}�[
	paral(false),//�}�q��Ԃ��H
	playerHitTimer(new CountDownTimer()),//�v���C���[�Ƃ̘A���q�b�g��h�����߁i���ꂪ�Ȃ��Ƃ��������u�ԂɎ��ʁj
	paralimitTimer(new CountDownTimer()), //�A���Ŗ�჏�ԂɂȂ�Ȃ����߂̃^�C�}�[
	sound(new Sound()),
	atTime(2.0f),
	attackTimer(new CountDownTimer(0.0f)),
	rush(false),
	mUpTimer(new CountUpTimer())
{
	*mPos = pos;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
	sound->Init();
	sound->Load("./Assets/Sound/deth.wav");
	sound->Load("./Assets/Sound/paral.wav");
}

RushEnemy::~RushEnemy() = default;

void RushEnemy::End()
{
	sound->PlaySE("./Assets/Sound/deth.wav");
	delete(mPos);
	delete(mSize);
	delete(mRenderer);

	delete(sRenderer);
	delete(paralRenderer);
	delete(paralimitTime);
	delete(paralimitTimer);
	delete(playerHitTimer);
	sound->Init();
	delete(sound);
	delete(attackTimer);
	delete(mUpTimer);
}

void RushEnemy::Update()
{
	if (GetDeath())return;

	playerHitTimer->Update();
	paralimitTimer->Update();
	mUpTimer->Update();
	Paralise();

	if (direction.x < 0) mRight = false;
	else if (direction.x > 0) mRight = true;

	if (!paral)
	{
		Rush();
	}
}

void RushEnemy::Draw()
{
	if (GetDeath())
	{
		//�����ɔ����̕`���
		return;
	}

	//�}�q��Ԃł̕`��
	if (paral)
	{
		SetDrawBright(255, 0, 0);
		int a = fmod(mUpTimer->Now() * 3, 2);
		mRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), a, *mSize, FALSE);
		SetDrawBright(255, 255, 255);
		paralRenderer->DrawAlternating(mPos->x, mPos->y, 3);
		return;
	}

	//�A�C�h����Ԃł̕`��
	if (!mStalker)
	{
		int t = fmod(mUpTimer->Now() * 3, 2);
		mRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), t, *mSize, FALSE);
	}
	//�ǐՏ�Ԃł̕`��
	if (mStalker)
	{
		//�ǐՍ�����
		if (!mRight)
		{
			int r = fmod(mUpTimer->Now() * 3, 1);
			sRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), r, *mSize, FALSE);
		}
		//�ǐՍ�����
		else if (mRight)
		{
			int l = fmod(mUpTimer->Now() * 3, 1);
			sRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), l, *mSize, TRUE);
		}
	}
}

void RushEnemy::Hit()
{
	for (auto && hit : mCollider->onCollisionStay())
	{

		if (hit->getOwner()->Tag() == "Wall" ||
			hit->getOwner()->Tag() == "FlyEnemy" ||
			hit->getOwner()->Tag() == "RushEnemy" ||
			hit->getOwner()->Tag() == "PatrolEnemy")
		{
			auto cPosX = hit->getOwner()->Position()->x;
			auto cPosY = hit->getOwner()->Position()->y;
			auto cSizeX = hit->getOwner()->Size()->x;
			auto cSizeY = hit->getOwner()->Size()->y;

			auto sx = cPosX + (cSizeX / 2);//�^��
			auto sy = cPosY + (cSizeY / 2);//�^��

			Vector2 dir = Vector2(old_x + (mSize->x / 2), mPos->y + (mSize->y / 2)) - Vector2(sx, sy);

			if (abs(dir.x) > abs(dir.y))
			{
				if (dir.x > 0)//����̉E�ɓ���������
				{
					mPos->x = cPosX + mSize->x + 1;
				}
				else//���ɓ���������
				{
					mPos->x = cPosX - mSize->x - 1;
				}
			}
			else
			{
				if (dir.y < 0)//����̉��ɓ���������
				{
					if (direction.y > 0)
					{
						mPos->y = cPosY - mSize->y;
						direction.y = 0;
					}
				}
				else//��ɓ���������
				{
					mPos->y = cPosY + cSizeY + 1;
					if (direction.y < 0)
					{
						direction.y = 0;
					}
				}
			}
		}
	}

	for (auto && hit : mCollider->onCollisionEnter())
	{
		auto cPosX = hit->getOwner()->Position()->x;
		auto cPosY = hit->getOwner()->Position()->y;
		auto cSizeX = hit->getOwner()->Size()->x;
		auto cSizeY = hit->getOwner()->Size()->y;
		auto sx = cPosX + (cSizeX / 2);//�^��
		auto sy = cPosY + (cSizeY / 2);//�^��
		Vector2 dir = Vector2(mPos->x + (mSize->x / 2), mPos->y + (mSize->y / 2)) - Vector2(sx, sy);

		if (hit->getOwner()->Tag() == "Wall" ||
			hit->getOwner()->Tag() == "FlyEnemy" ||
			hit->getOwner()->Tag() == "RushEnemy" ||
			hit->getOwner()->Tag() == "PatrolEnemy")
		{
			if (abs(dir.x) > abs(dir.y))
			{
				if (dir.x > 0)//����̉E�ɓ���������
				{
					mPos->x = cPosX + mSize->x;
					if (direction.x < 0)
					{
						direction.x = 0;
					}
				}
				else//���ɓ���������
				{
					mPos->x = cPosX - mSize->x;
					if (direction.x < 0)
					{
						direction.x = 0;
					}
				}
			}
			else
			{
				if (dir.y < 0)//����̉��ɓ���������
				{
					mPos->y = cPosY - mSize->y;
					if (direction.y > 0)
					{
						mPos->y = cPosY - mSize->y;
					}
				}
				else//��ɓ���������
				{
					mPos->y = cPosY + cSizeY + 1;
					if (direction.y < 0)
					{
						direction.y = 0;
					}
				}
			}
		}
	}
}

void RushEnemy::ToPlayer()
{
	//�v���C���[�����͈͂ɂ͂�������aqrt
	if (std::sqrtf(std::powf(pPos.x - mPos->x, 2) + std::powf(pPos.y - mPos->y, 2)) < staSize)
	{
		mStalker = true;
	}
}

void RushEnemy::Rush()
{
	pPos = GetActorManager()->GetPlayer()->GetPosition();
	ToPlayer();
	//�ǐՏ�ԂŃ}�q��ԂłȂ����
	if (mStalker && !paral)
	{
		attackTimer->Update();

		if (attackTimer->IsTime())
		{
			psPos = pPos;
			Actor::SetPos(*mPos);
			old_x = mPos->x;
			old_y = mPos->y;
			direction.x = psPos.x - old_x;
			direction.y = psPos.y - old_y;
			direction.normalize();

			mPos->x += direction.x*speed;
			mPos->y += direction.y*speed;

			attackTimer->SetTime(atTime);
		}
	}
}

void RushEnemy::Paralise()
{
	if (!paralimitTimer->IsTime())
	{
		SetElectricShock(false);
	}
	//paralimitTime->Update();
	if (GetElectricShock() && !paral)
	{
		paral = true;
		sound->PlaySE("./Assets/Sound/paral.wav");
		//paralimitTime->SetTime(paraTime);
		mElectricTimer->SetTime(paraTime);
		playerHitTimer->SetTime(0.3f);
	}

	if (mElectricTimer->IsTime())//(paralimitTime->IsTime())
	{
		paral = false;
		SetElectricShock(false);
		paralimitTimer->SetTime(0.01f);
	}
}
