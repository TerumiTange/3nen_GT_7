#include "SmallEnemy.h"

SmallEnemy::SmallEnemy(const Vector2 & pos, const char * tag) :
	Actor(tag),
	mCollider(new ColliderComponent(this)),
	mPos(new Vector2(0, 0)),
	mSize(new Vector2(32, 32)),
	mFilename(tag),
	mRenderer(new Renderer(tag)),
	mFall(true),
	mRight(true)
{
	*mPos = pos;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
}

SmallEnemy::~SmallEnemy() = default;

void SmallEnemy::End()
{
	delete(mPos);
	delete(mSize);
	delete(mRenderer);
}

void SmallEnemy::Update()
{
	Actor::SetPos(*mPos);
	if (mFall)
	{
		mPos->y += 10;
	}
	mFall = true;
	old_x = mPos->x;
	old_y = mPos->y;
	if (mRight)
	{
		mPos->x += 5;
	}
	else
	{
		mPos->x -= 5;
	}
}

void SmallEnemy::Draw()
{
	mRenderer->Draw(*mPos);
	//test—p
	//int a;
	//a = LoadGraph("./Assets/Texture/Enemy.png");
	//DrawGraph(mPos->x, mPos->y, a, TRUE);
	//DeleteGraph(a);
}

void SmallEnemy::Hit()
{
}
/*
void SmallEnemy::Hit(std::list<std::shared_ptr<Actor>> actors)
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
		
	}
}

void SmallEnemy::Hit(const char * tag, std::shared_ptr<Vector2> pos, std::shared_ptr<Vector2> size)
{
}
*/
bool SmallEnemy::CheckHit(int x, int y, int width, int height)
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
