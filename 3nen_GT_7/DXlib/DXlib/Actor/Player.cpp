#include "Player.h"
#include <algorithm>
#define NOMINMAX
#define max(a,b)            (((a) > (b)) ? (a) : (b))

Player::Player(const char* tag):
	Actor(tag),
	mPos(new Vector2(0,0)),
	mVelocity(new Vector2(0,0)),
	maxSpeed(10),
	mAcceleration(0.5),
	mSize(new Vector2(64,64)),
	mFilename(tag),
	mRenderer(new Renderer()),
	mInput(new Input()),
	mFall(true),
	mJump(false),
	mFloating(false),
	mElectricity(0),
	mChargedState(false),
	mPoppedState(false)
{
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
	mRenderer->LoadTexture(mFilename);
	mInput->Init();
}

Player::Player(const Vector2& position, const char* tag):
	Actor(tag),
	mPos(new Vector2(0,0)),
	mVelocity(new Vector2(0, 0)),
	maxSpeed(10),
	mAcceleration(0.5),
	mSize(new Vector2(64, 64)),
    mFilename(tag),
	mRenderer(new Renderer()),
	mInput(new Input()),
	mFall(true),
	mJump(false),
	mFloating(false),
	mElectricity(0),
	mChargedState(false),
	mPoppedState(false)
{
	mPos->x = position.x;
	mPos->y = position.y;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
	mRenderer->LoadTexture(mFilename);
	mInput->Init();
}

Player::~Player() = default;

void Player::End()
{
	delete(mPos);
	delete(mVelocity);
	delete(mSize);
	delete(mRenderer);
	delete(mInput);
}

void Player::Init()
{
	
}

void Player::Update()
{
	Actor::SetPos(*mPos);

	if (!mFloating)//浮遊状態でなければ
	{
		mElectricity++;
		if (mElectricity > 100)mElectricity = 100;
	}

	if (mFall&&(!mFloating))//重力
	{
		mPos->y += 20;
	}

	mFall = true;
	old_x = mPos->x;
	old_y = mPos->y;

	if (mInput->GetKey(A)||mInput->GetKey(LEFTARROW))//左
	{
		//mPos->x -= 10;
		mVelocity->x = min(mVelocity->x - mAcceleration, -maxSpeed);
	}
	else if(mInput->GetKey(D) || mInput->GetKey(RIGHTARROW))//右
	{
		//mPos->x += 10;
		mVelocity->x = max(mVelocity->x + mAcceleration, maxSpeed);
	}

	if (!mJump && mInput->GetKeyDown(SPACE) && mElectricity >= 10)//ジャンプ
	{
		mElectricity -= 10;
		mPos->y -= 64;
		mJump = true;
	}
	else if (mJump && mInput->GetKeyDown(SPACE))//浮遊
	{
		if (mElectricity > 0)
		{
			mFloating = true;
			mElectricity--;
		}
		else
		{
			mFloating = false;
			mFall = true;
		}
	}
	if (mInput->GetKeyUp(SPACE))
	{
		mFloating = false;
	}
	if (mElectricity < 0)//もし0よりも小さくなったら
	{
		mElectricity = 0;
	}
	clsDx();
	printfDx("落ちているかどうか_%d", mFall);
	printfDx("現在のゲージ_%d", mElectricity);
	printfDx("ジャンプしているかどうか_%d", mJump);
	printfDx("浮遊しているかどうか_%d", mFloating);
	mPos->x += mVelocity->x;//移動処理
	mVelocity->x *= 0.8;//ここで慣性性が出る
}

void Player::Draw()
{
	mRenderer->Draw(mFilename, *mPos);
	//test用
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
		if (a->Tag() == "Wall")
		{
			if (CheckHit( a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				mPos->x = old_x;
				
				//if (mPos->x <= a->Position()->x + a->Size()->x)
				//{
				//	mPos->x = a->Position()->x + a->Size()->x;
				//}
				//else if (mPos->x < a->Position()->x + a->Size()->x)
				//{
				//	mPos->x = a->Position()->x - mSize->x;
				//}
				//else if (mPos->x + mSize->x < a->Position()->x)
				//{
				//	mPos->x = a->Position()->x - mSize->x;
				//}
				//else
				//{
				//	mPos->x = old_x;
				//}
			}
		}

		if (a->Tag() == "Floor")
		{
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				mFall = false;//重力が発生していない
				mJump = false;//ジャンプしていない
				mFloating = false;//浮遊していない
				mPos->y = a->Position()->y - mSize->y;
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



