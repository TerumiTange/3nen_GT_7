#include "FlyEnemy.h"

FlyEnemy::FlyEnemy(const Vector2 & pos, const char * tag) :
	Actor(tag),
	mPos(new Vector2(0, 0)),
	mSize(new Vector2(32, 32)),
	mFilename(tag),
	mRenderer(new Renderer(tag)),
	mFall(false),
	mRight(true),
	mStalker(false),
	staSize(new Vector2(128, 128))
{
	*mPos = pos;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
}

FlyEnemy::~FlyEnemy() = default;

void FlyEnemy::End()
{
	delete(mPos);
	delete(mSize);
	delete(mRenderer);

	delete(staSize);
}

void FlyEnemy::Update()
{
	Move();
}

void FlyEnemy::Draw()
{
	mRenderer->Draw(*mPos);
}

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
				mPos->x = old_x;
				if (mRight)mRight = false;
				else mRight = true;
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
			//�v���C���[�ƕ��ʂɂԂ������Ƃ�
			/*if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{

			}*/

			//�v���C���[�����͈͓��ɓ������Ƃ�
			if (CheckHit(a->Position()->x - 64, a->Position()->y - 64, 192, 192))
			{
				/*mStalker = true;
				pPos.x = a->Position()->x;
				pPos.y = a->Position()->y;*/
				Actor::Destroy(a);
			}
		}

	}
}

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

void FlyEnemy::Move()
{
	if (mStalker)
	{
		//�����ɓ���������
		Actor::SetPos(*mPos);
		old_x = mPos->x;
		old_y = mPos->y;
		direction.x = pPos.x - old_x;
		direction.y = pPos.y - old_y;
		direction.normalize();

		mPos->x += direction.x;
		mPos->y += direction.y;
	}
	/*if (mStalker)
	{
		if (mRight)
		{
			mPos->x += 5;
		}
		else
		{
			mPos->x -= 5;
		}
	}*/
}

void FlyEnemy::Fall()
{

}