#include "PatrolEnemy.h"
#include "ActorManager.h"
#include "Player.h"
#include "../Collider//ComponentManager.h"

PatrolEnemy::PatrolEnemy(const Vector2 & pos, const char * tag) :
	Actor(tag),
	mCollider(new ColliderComponent(this)),
	mPos(new Vector2(0, 0)),//�|�W�V����
	mSize(new Vector2(32, 32)),//�T�C�Y
	mFilename(tag),//
	mRenderer(new Renderer("Enemy2IDL")),//�A�C�h����Ԃ̉摜
	mFall(false),//�d��
	mRight(true),
	mStalker(false),//�ǐՏ�Ԃ��H
	staSize(200),//�ǐՔ͈�
	sRenderer(new Renderer("EnemyMove")),//�ǐՏ�Ԃ̉摜
	paralRenderer(new Renderer("ThunderEffect")),//�}�q��Ԃ̉摜
	speed(8.0f),//���x
	paraTime(4.0f),//�}�q����
	paralimitTime(new CountDownTimer()),//�}�q���Ԃ̃^�C�}�[
	paral(false),//�}�q��Ԃ��H
	playerHitTimer(new CountDownTimer()),//�v���C���[�Ƃ̘A���q�b�g��h�����߁i���ꂪ�Ȃ��Ƃ��������u�ԂɎ��ʁj
	paralimitTimer(new CountDownTimer()), //�A���Ŗ�჏�ԂɂȂ�Ȃ����߂̃^�C�}�[
	sound(new Sound()),
	patrolPos(0),
	mPatrol(true),//�����Ԃ��H
	pspeed(1.0f),
	mUpTimer(new CountDownTimer())
{
	*mPos = pos;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
	sound->Init();
	sound->Load("./Assets/Sound/deth.wav");
	sound->Load("./Assets/Sound/paral.wav");

	//����̃|�W�V����
	patrolPos.push_back(Vector2(pos.x - 64, pos.y - 64));//1�ʒu
	patrolPos.push_back(Vector2(pos.x - 64, pos.y + 64));//2�ʒu
	patrolPos.push_back(Vector2(pos.x + 64, pos.y + 64));//3�ʒu
	patrolPos.push_back(Vector2(pos.x + 64, pos.y - 64));//4�ʒu
	patrolPos.push_back(Vector2(pos));//�ǐՌ�ɖ߂�ʒu
}

PatrolEnemy::~PatrolEnemy() = default;

void PatrolEnemy::End()
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
	delete(mUpTimer);

	patrolPos.clear();
}

void PatrolEnemy::Update()
{
	playerHitTimer->Update();
	paralimitTimer->Update();
	mUpTimer->Update();
	Paralise();

	if (direction.x < 0) mRight = false;
	else if (direction.x > 0) mRight = true;

	if (!paral)//�}�q��ԂłȂ��Ȃ�
	{
		Move();
		Patrol();
	}
}

void PatrolEnemy::Draw()
{
	//�}�q��Ԃł̕`��
	if (paral)
	{
		int a = fmod(mUpTimer->Now() * 3, 1);
		mRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), a, *mSize, FALSE);
		paralRenderer->Draw(mPos->x - 16, mPos->y + 32);
		return;
	}

	//�A�C�h����Ԃł̕`��
	if (!mStalker)
	{
		int t = fmod(mUpTimer->Now() * 3, 4);
		mRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), t, *mSize, FALSE);
	}
	//�ǐՏ�Ԃł̕`��
	if (mStalker)
	{
		//�ǐՍ�����
		if (!mRight)
		{
			int r = fmod(mUpTimer->Now() * 3, 4);
			sRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), r, *mSize, FALSE);
		}
		//�ǐՍ�����
		else if (mRight)
		{
			int l = fmod(mUpTimer->Now() * 3, 4);
			sRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), l, *mSize, TRUE);
		}
	}
}

void PatrolEnemy::Hit()
{
	for (auto && hit : mCollider->onCollisionStay())
	{
		auto cPosX = hit->getOwner()->Position()->x;
		auto cPosY = hit->getOwner()->Position()->y;
		auto cSizeX = hit->getOwner()->Size()->x;
		auto cSizeY = hit->getOwner()->Size()->y;

		if (hit->getOwner()->Tag() == "Wall")
		{
			if (old_y < cPosY)//��������
			{
				mPos->y = cPosY - mSize->y;
			}
			else if (old_y > cPosY)//����������
			{
				mPos->y = cPosY + cSizeY + 1;
			}
			else if (old_x < cPosX)//��������
			{
				mPos->x = cPosX - mSize->x;
			}
			else if (old_x > cPosX)//�������E
			{
				mPos->x = cPosX + mSize->x;
			}
		}
	}

	for (auto && hit : mCollider->onCollisionEnter())
	{
		auto cPosX = hit->getOwner()->Position()->x;
		auto cPosY = hit->getOwner()->Position()->y;
		auto cSizeX = hit->getOwner()->Size()->x;
		auto cSizeY = hit->getOwner()->Size()->y;

		if (hit->getOwner()->Tag() == "Wall")
		{
			if (old_y < cPosY)//��������
			{
				mPos->y = cPosY - mSize->y;
			}
			else if (old_y > cPosY)//��������
			{
				mPos->y = cPosY + cSizeY;
			}
			else if (old_x < cPosX)//��������
			{
				mPos->x = cPosX - mSize->x;
			}
			else if (old_x > cPosX)//�������E
			{
				mPos->x = cPosX + mSize->x + 1;
			}
		}
	}
}

void PatrolEnemy::ToPlayer()
{
	//�v���C���[�����͈͂ɂ͂�������aqrt
	if (std::sqrtf(std::powf(pPos.x - mPos->x, 2) + std::powf(pPos.y - mPos->y, 2)) < staSize)
	{
		mStalker = true;
		mPatrol = false;
	}
	else
	{
		mStalker = false;
	}
}
void PatrolEnemy::Move()
{
	pPos = GetActorManager()->GetPlayer()->GetPosition();
	ToPlayer();
	//�ǐՏ�ԂŃ}�q��ԂłȂ����
	if (mStalker && !paral)
	{
		Actor::SetPos(*mPos);
		old_x = mPos->x;
		old_y = mPos->y;
		direction.x = pPos.x - old_x;
		direction.y = pPos.y - old_y;
		direction.normalize();

		mPos->x += direction.x*speed;
		mPos->y += direction.y*speed;
	}
}

void PatrolEnemy::Paralise()//��჏�Ԃ̏���
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

void PatrolEnemy::Patrol()
{
	if (mPatrol)
	{
		switch (patrolcount)
		{
		case 0:
			PatrolMove();

			if (old_x == a.x && old_y == a.y)
			{
				patrolcount = 1;
			}
			break;

		case 1:
			PatrolMove();

			if (old_x == a.x && old_y == a.y)
			{
				patrolcount = 2;
			}
			break;

		case 2:
			PatrolMove();

			if (old_x == a.x && old_y == a.y)
			{
				patrolcount = 3;
			}
			break;

		case 3:
			PatrolMove();

			if (old_x == a.x && old_y == a.y)
			{
				patrolcount = 0;
			}
			break;
		}
	}

	if (!mStalker && !mPatrol)
	{
		patrolcount = 4;

		PatrolMove();

		if (old_x == a.x && old_y == a.y)
		{
			mPatrol = true;
			patrolcount = 0;
		}
	}
}

void PatrolEnemy::PatrolMove()
{
	old_x = mPos->x;
	old_y = mPos->y;
	a = patrolPos[patrolcount];
	direction.x = a.x - old_x;
	direction.y = a.y - old_y;
	direction.normalize();

	mPos->x += direction.x*pspeed;
	mPos->y += direction.y*pspeed;
}