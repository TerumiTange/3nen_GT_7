#include "Player.h"

Player::Player(const char* tag):
	Actor(tag),
	mPos(new Vector2(0,0)),
	mSize(new Vector2(64,64)),
	mFilename("Player.png"),
	mRenderer(new Renderer()),
	mInput(new Input()),
	mFall(true),
	mElectricity(0),
	mChargedState(false),
	mPoppedState(false)
{
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
}

Player::Player(const Vector2& position, const char* tag):
	Actor(tag),
	mPos(new Vector2(0,0)),
	mSize(new Vector2(64, 64)),
    mFilename(tag),
	mRenderer(new Renderer()),
	mInput(new Input()),
	mFall(true),
	mElectricity(0),
	mChargedState(false),
	mPoppedState(false)
{
	mPos->x = position.x;
	mPos->y = position.y;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
}

Player::~Player() = default;

void Player::Init()
{
	mInput->Init();
}

void Player::Update()
{
	Actor::SetPos(*mPos);
	if (mFall)//d—Í
	{
		mPos->y += 20;
	}
	mFall = true;
	old_x = mPos->x;
	old_y = mPos->y;
	if (mInput->GetKey(A)||mInput->GetKey(LEFTARROW))
	{
		mPos->x -= 10;
	}
	else if(mInput->GetKey(D) || mInput->GetKey(RIGHTARROW))
	{
		mPos->x += 10;
	}

}

void Player::Draw()
{
	//renderer.Draw(filename, *pos);
	//test—p
	int a;
	a = LoadGraph("./Assets/Texture/Player.png");
	DrawGraph(mPos->x, mPos->y, a, TRUE);
	DeleteGraph(a);
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
				mFall = false;
			}
		}
		if (a->Tag() == "Enemy")
		{
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				
			}
		}
	}
}

bool Player::CheckHit(int x, int y, int width, int height)
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



