#include "SmallEnemy.h"
#include "../Device/Renderer.h"

SmallEnemy::SmallEnemy(const Vector2 & pos, const char * tag) :
	Actor(tag),
	mPos(new Vector2(0, 0)),
	mSize(new Vector2(32, 32)),
	mFilename(tag),
	mRenderer(new Renderer()),
	mFall(true),
	mRight(true)
{
	*mPos = pos;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
}

SmallEnemy::~SmallEnemy() = default;

void SmallEnemy::Update()
{
	Actor::SetPos(*mPos);
	if (mFall)
	{
		mPos->y += 20;
	}
	mFall = true;
	old_x = mPos->x;
	old_y = mPos->y;
	if (mRight)
	{
		mPos->x += 10;
	}
	else
	{
		mPos->x -= 10;
	}
}

void SmallEnemy::Draw()
{
	mRenderer->Draw(mFilename, *mPos);
	//test—p
	//int a;
	//a = LoadGraph("./Assets/Texture/Enemy.png");
	//DrawGraph(mPos->x, mPos->y, a, TRUE);
	//DeleteGraph(a);
}

void SmallEnemy::Hit(std::list<std::shared_ptr<Actor>> actors)
{
	for (auto& a : actors)
	{
		if (a->Tag() == "Player")
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
	}
}

bool SmallEnemy::CheckHit(int x, int y, int width, int height)
{
	int L1 = mPos->x;
	int R1 = mPos->x + mSize->x;
	int L2 = x;
	int R2 = x + width;
	int U1 = mPos->y;
	int D1 = mPos->y + mSize->y;
	int U2 = y;
	int D2 = y + height;
	if (R1 < L2)return false;
	if (R2 < L1)return false;
	if (D1 < U2)return false;
	if (D2 < U1)return false;
	return true;
}
