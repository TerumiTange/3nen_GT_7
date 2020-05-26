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
	mRenderer(new Renderer("Enemy")),//�A�C�h����Ԃ̉摜
	mFall(false),//�d��
	mRight(true),
	mStalker(false),//�ǐՏ�Ԃ��H
	staSize(200),//�ǐՔ͈�
	sRenderer(new Renderer("Enemy2")),//�ǐՏ�Ԃ̉摜
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
	pspeed(1.0f)
{
	*mPos = pos;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
	sound->Init();
	sound->Load("./Assets/Sound/deth.wav");
	sound->Load("./Assets/Sound/paral.wav");

	//����̃|�W�V����
	patrolPos.push_back(Vector2(96.0f, 96.0f));//1�ʒu
	patrolPos.push_back(Vector2(96.0f, 128.0f));//2�ʒu
	patrolPos.push_back(Vector2(128.0f, 128.0f));//3�ʒu
	patrolPos.push_back(Vector2(128.0f, 96.0f));//4�ʒu
	patrolPos.push_back(Vector2(320.0f, 160.0f));//�ǐՌ�ɖ߂�ʒu
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

	patrolPos.clear();
}

void PatrolEnemy::Update()
{
	playerHitTimer->Update();
	paralimitTimer->Update();
	Paralise();
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
		mRenderer->Draw(*mPos);
		paralRenderer->Draw(mPos->x - 16, mPos->y + 32);
		return;
	}

	//�A�C�h����Ԃ̕`��
	if (!mStalker)
	{
		mRenderer->Draw(*mPos);
	}

	//�ǐՏ�Ԃł̕`��
	if (mStalker)
	{
		sRenderer->Draw(*mPos);
	}
}

void PatrolEnemy::Hit()
{
	for (auto && hit : mCollider->onCollisionEnter())
	{
		if (hit->getOwner()->Tag() == "Wall")
		{
			auto cPosX = hit->getOwner()->Position()->x;
			auto cPosY = hit->getOwner()->Position()->y;
			auto cSizeX = hit->getOwner()->Size()->x;
			auto cSizeY = hit->getOwner()->Size()->y;

			if (mPos->y + mSize->y >= cPosY)//�����̉��ɂ�������
			{
				mPos->y = cPosY - mSize->y;
			}
		}
	}

	for (auto && hit : mCollider->onCollisionStay())
	{
		if (hit->getOwner()->Tag() == "Wall")
		{
			auto cPosX = hit->getOwner()->Position()->x;
			auto cPosY = hit->getOwner()->Position()->y;
			auto cSizeX = hit->getOwner()->Size()->x;
			auto cSizeY = hit->getOwner()->Size()->y;

			if (mPos->y + mSize->y >= cPosY)//�����̉��ɂ�������
			{
				mPos->y = cPosY - mSize->y;
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