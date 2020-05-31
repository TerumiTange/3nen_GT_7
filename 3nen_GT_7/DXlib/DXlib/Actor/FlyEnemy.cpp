#include "FlyEnemy.h"
#include "ActorManager.h"
#include "Player.h"
#include "../Collider/ComponentManager.h"

FlyEnemy::FlyEnemy(const Vector2 & pos, const char * tag) :
	Actor(tag),
	mCollider(new ColliderComponent(this)),
	mPos(new Vector2(0, 0)),//�|�W�V����
	mSize(new Vector2(32, 32)),//�T�C�Y
	mFilename(tag),//
	mRenderer(new Renderer("EnemyIDL")),//�A�C�h����Ԃ̉摜
	mFall(false),//�d��
	mRight(false),
	mStalker(false),//�ǐՏ�Ԃ��H
	staSize(200),//�ǐՔ͈�
	sRenderer(new Renderer("EnemyTargetOn")),//�ǐՏ�Ԃ̉摜
	paralRenderer(new Renderer("ThunderEffect")),//�}�q��Ԃ̉摜
	speed(5.0f),//���x
	paraTime(4.0f),//��჎���
	paralimitTime(new CountDownTimer()),//��჎��Ԃ̃^�C�}�[
	paral(false),//��჏�Ԃ��ǂ���
	playerHitTimer(new CountDownTimer()),//�v���C���[�Ƃ̘A���q�b�g��h�����߁i���ꂪ�Ȃ��Ƃ��������u�ԂɎ��ʁj
	paralimitTimer(new CountDownTimer()), //�A���Ŗ�჏�ԂɂȂ�Ȃ����߂̃^�C�}�[
	sound(new Sound()),
	mUpTimer(new CountUpTimer())
{
	*mPos = pos;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
	sound->Init();
	sound->Load("./Assets/Sound/deth.wav");
	sound->Load("./Assets/Sound/paral.wav");
}

FlyEnemy::~FlyEnemy() = default;

void FlyEnemy::End()
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
}

void FlyEnemy::Update()
{
	if (GetDeath())return;

	playerHitTimer->Update();//
	paralimitTimer->Update();//
	mUpTimer->Update();
	Paralise();//

	if (direction.x < 0) mRight = false;
	else if (direction.x > 0) mRight = true;

	if (!paral)//��჏�ԂłȂ��Ȃ�
	{
		Move();
	}
}

void FlyEnemy::Draw()
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
		int b = fmod(mUpTimer->Now() * 3, 3);
		paralRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), b, *mSize, FALSE);
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

void FlyEnemy::Hit()
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

void FlyEnemy::ToPlayer()
{
	//�v���C���[�����͈͂ɂ͂�������sqrt
	if (std::sqrtf(std::powf(pPos.x - mPos->x, 2) + std::powf(pPos.y - mPos->y, 2)) < staSize)
	{
		mStalker = true;
	}
	else
	{
		mStalker = false;
	}
}
/*
void FlyEnemy::Hit(std::list<std::shared_ptr<Actor>> actors)
{
	for (auto& a : actors)
	{
		if (a->Tag() == "Metal")
		{
			//mFall = false;
			//mPos->y = a->Position()->y - mSize->y;
			//mPos->x = old_x;
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				if (mRight)mRight = false;
				else mRight = true;
			}
		}
		if (a->Tag() == "Wall")
		{
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				//mPos->x = old_x;
				//if (mRight)mRight = false;
				//else mRight = true;

				if (old_y + mSize->y <= a->Position()->y)//�����̉��ɓ��������Ƃ�
				{
					mPos->y = a->Position()->y - mSize->y;
				}
				else if (old_y > a->Position()->y + a->Size()->y)//�����̏�ɓ��������Ƃ�
				{
					mPos->y = a->Position()->y + a->Size()->y;
				}
				else if (old_x >= a->Position()->x + a->Size()->x)//�����̍��ɓ��������Ƃ�
				{
					mPos->x = a->Position()->x + a->Size()->x + 1;
					mRight = true;
				}

				else if (old_x + mSize->x <= a->Position()->x)//�����̉E�ɓ��������Ƃ�
				{
					mPos->x = a->Position()->x - mSize->x - 1;
					mRight = false;
				}
			}
		}
		if (a->Tag() == "Floor")
		{
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				mFall = false;
				//mPos->y = old_y;
				mPos->y = a->Position()->y - mSize->y;
			}
		}

		if (a->Tag() == "Player")
		{
			if (playerHitTimer->IsTime())//�v���C���[�ƘA���q�b�g��h������
			{
				//�v���C���[�ƕ��ʂɂԂ������Ƃ�
				if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
				{
					if (paral&&playerHitTimer->IsTime())//��჏�ԂȂ�
					{
						//Destroy(this);//�������S
						for (auto act : actors)
						{
							if (act->GetElectricShock())
							{
								Destroy(act);//��჏�Ԃ̓G�S�����S
							}
						}
					}
				}
			}

			//�v���C���[�����͈͓��ɓ������Ƃ��i�ǐՔ͈͂ɓ������Ƃ��j
			if (CheckHit2(a->Position()->x - 64, a->Position()->y - 64, a->Size()->x, a->Size()->y, staSize))
			{
				mStalker = true;
				pPos.x = a->Position()->x;
				pPos.y = a->Position()->y;
			}

			//�v���C���[�����͈͂��痣�ꂽ�Ƃ��i�ǐՔ͈͂���o���Ƃ��j
			//�͈͂̑傫���ɕύX���K�v�ȏꍇ�A����
			if (!CheckHit2(a->Position()->x - 64, a->Position()->y - 64, a->Size()->x, a->Size()->y, staSize))
			{
				mStalker = false;
			}
		}

		if (a->Tag() == "FlyEnemy")
		{
			if (CheckHit2(a->Position()->x - 64, a->Position()->y - 64, a->Size()->x, a->Size()->y, 100))
			{
				if (!a->GetElectricShock() && paral)//���g���}�q��Ԃő��肪�}�q��ԂłȂ��Ȃ�
				{
					a->SetElectricShock(true);
					//SetElectricShock(true);
					//paralimitTime->SetTime(paraTime);
				}
			}
		}
	}
}

void FlyEnemy::Hit(const char * tag, std::shared_ptr<Vector2> pos, std::shared_ptr<Vector2> size)
{
	if (tag == "Wall")
	{
		if (old_y + mSize->y <= pos->y)//�����̉��ɓ��������Ƃ�
		{
			mPos->y = pos->y - mSize->y;
		}
		else if (old_y > pos->y + size->y)//�����̏�ɓ��������Ƃ�
		{
			mPos->y = pos->y + size->y;
		}
		else if (old_x >= pos->x + size->x)//�����̍��ɓ��������Ƃ�
		{
			mPos->x = pos->x + size->x + 1;
		}

		else if (old_x + mSize->x <= pos->x)//�����̉E�ɓ��������Ƃ�
		{
			mPos->x = pos->x - mSize->x - 1;
		}
	}

	if (tag == "Player")
	{
		if (playerHitTimer->IsTime())//�v���C���[�ƘA���q�b�g��h������
		{
			SetElectricShock(true);
			if (paral)
			{
				Destroy(this);
			}
		}
	}
}
*/
/*
bool FlyEnemy::CheckHit(int x, int y, int width, int height)
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

bool FlyEnemy::CheckHit2(int x, int y, int width, int height, int p)
{
	if (mPos->x + mSize->x + p < x)return false;
	if (x + width < mPos->x - p) return false;
	if (mPos->y - p > y + height) return false;
	if (mPos->y + width + p < y) return false;
	return true;
}
*/
void FlyEnemy::Move()
{
	pPos = GetActorManager()->GetPlayer()->GetPosition();
	ToPlayer();

	//�ǂ��������ԂŖ�჏�ԂłȂ����
	if (mStalker && !paral)
	{
		//�����ɓ���������
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

void FlyEnemy::Fall()
{

}

void FlyEnemy::Paralise()//��჏�Ԃ̏���
{
	//if (!paralimitTimer->IsTime() && !paralimitTime->IsTime())
	//{
	//	SetElectricShock(false);
	//}
	//else if (Actor::GetElectricShock())
	//{
	//	paral = true;
	//	Actor::SetElectricShock(false);
	//	paralimitTime->SetTime(paraTime);
	//}
	//if (paral)
	//{
	//	paralimitTime->Update();
	//	if (paralimitTime->IsTime())
	//	{
	//		paral = false;
	//		Actor::SetElectricShock(false);
	//		playerHitTimer->SetTime(0.3f);
	//		paralimitTimer->SetTime(0.2f);
	//	}
	//}
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
