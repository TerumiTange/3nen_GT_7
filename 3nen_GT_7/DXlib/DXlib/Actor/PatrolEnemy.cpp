#include "PatrolEnemy.h"
#include "ActorManager.h"
#include "Player.h"
#include "../Collider//ComponentManager.h"

PatrolEnemy::PatrolEnemy(const Vector2 & pos, const Vector2 & patpos1, const Vector2 & patpos2, const Vector2 & patpos3, const Vector2 & patpos4, const char * tag) :
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
	mPatrol(false),//�����Ԃ��H
	pspeed(5.0f),
	mUpTimer(new CountUpTimer())
{
	*mPos = pos;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
	sound->Init();
	sound->Load("./Assets/Sound/deth.wav");
	sound->Load("./Assets/Sound/paral.wav");

	//����̃|�W�V����
	patrolPos.push_back(Vector2(patpos1.x, patpos1.y));//1�ʒu
	patrolPos.push_back(Vector2(patpos2.x, patpos2.y));//2�ʒu
	patrolPos.push_back(Vector2(patpos3.x, patpos3.y));//3�ʒu
	patrolPos.push_back(Vector2(patpos4.x, patpos4.y));//4�ʒu
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
	if (GetDeath())return;

	if (GetDeath())return;
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
	if (GetDeath())
	{
		//�����ɔ����̕`���
		return;
	}

	//�}�q��Ԃł̕`��
	if (paral)
	{
		SetDrawBright(255, 0, 0);
		int a = fmod(mUpTimer->Now() * 3, 1);
		sRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), a, *mSize, FALSE);
		SetDrawBright(255, 255, 255);
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

			if (old_x >= a.x && old_y <= a.y)
			{
				patrolcount = 1;
			}
			break;

		case 1:
			PatrolMove();

			if (old_x >= a.x && old_y >= a.y)
			{
				patrolcount = 2;
			}
			break;

		case 2:
			PatrolMove();

			if (old_x <= a.x && old_y >= a.y)
			{
				patrolcount = 3;
			}
			break;

		case 3:
			PatrolMove();

			if (old_x <= a.x && old_y <= a.y)
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

		if (old_x <= a.x && old_y <= a.y)
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