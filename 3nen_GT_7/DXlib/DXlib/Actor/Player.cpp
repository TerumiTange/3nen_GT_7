#include "Player.h"
#include <algorithm>
#define NOMINMAX
#define max(a,b)            (((a) > (b)) ? (a) : (b))


Player::Player(const Vector2& position, const char* tag):
	Actor(tag),
	mGoal(false),
	mPos(new Vector2(0,0)),
	mVelocity(new Vector2(0, 0)),
	maxSpeed(7),
	mAcceleration(0.5),
	mSize(new Vector2(64, 64)),
    mFilename(tag),
	mRenderer(new Renderer(tag)),
	mStaticElectricity(new Renderer("ThunderEffect")),
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
	mInput->Init();
}

Player::~Player() = default;

void Player::End()
{
	delete(mPos);
	delete(mVelocity);
	delete(mSize);
	delete(mRenderer);
	delete(mStaticElectricity);
	delete(mInput);
}

void Player::Init()
{
	
}

void Player::Update()
{
	mInput->JoyUpdate();
	Actor::SetPos(*mPos);

	if (!mFloating)//浮遊状態でなければ
	{
		mElectricity++;
		if (mElectricity > 100)mElectricity = 100;
	}

	if (mFall&&(!mFloating))//重力
	{
		mPos->y += 16;
	}

	mFall = true;
	old_x = mPos->x;
	old_y = mPos->y;

	if (!mPoppedState)
	{
		Move();
	}
	

	mPos->y += mVelocity->y;
	mVelocity->y *= 0.7f;
	mPos->x += mVelocity->x;//移動処理
	mVelocity->x *= 0.9f;//ここで慣性性が出る

	if (abs(mVelocity->x) <= 0.5f)
	{
		mPoppedState = false;
	}
}
void Player::Move()
{
	if (mInput->GetKey(A) || mInput->GetKey(LEFTARROW))//左
	{
		//mPos->x -= 10;
		mVelocity->x = min(mVelocity->x - mAcceleration, -maxSpeed);
	}
	else if (mInput->GetKey(D) || mInput->GetKey(RIGHTARROW))//右
	{
		//mPos->x += 10;
		mVelocity->x = max(mVelocity->x + mAcceleration, maxSpeed);
	}

}

void Player::Jump()
{
	if (!mJump && mInput->GetKeyDown(SPACE) && mElectricity >= 10)//ジャンプ
	{
		mElectricity -= 10;
		//mPos->y -= 64;
		mVelocity->y = -32;
		mJump = true;
	}

	if (!mJump&&mElectricity >= 10 && mInput->PadDown(JoyCode::Joy_A))
	{
		mElectricity -= 10;
		//mPos->y -= 64;
		mVelocity->y = -32;
		mJump = true;
	}
}

void Player::Floating()
{
	if (mJump && (mInput->GetKeyDown(SPACE) || mInput->PadDown(JoyCode::Joy_A)))//浮遊
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
	if (mInput->GetKeyUp(SPACE) && mInput->PadUp(JoyCode::Joy_A))
	{
		mFloating = false;
	}
	if (mElectricity < 0)//もし0よりも小さくなったら
	{
		mElectricity = 0;
	}
}

void Player::Draw()
{
	mRenderer->Draw(*mPos);
	if (mPoppedState)
	{
		mStaticElectricity->Draw(mPos->x - 16, mPos->y + 32);
	}
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
		if (a->Tag() == "DeathBlock")
		{
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				Actor::Destroy(this);
			}
		}
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
				mFall = false;//重力が発生していない
				mJump = false;//ジャンプしていない
				mFloating = false;//浮遊していない
				mPos->y = a->Position()->y - mSize->y;
			}
		}
		if (a->Tag() == "Metal")
		{
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				if (!mPoppedState)
				{
					//mRenderer->Draw("ThunderEffect", *mPos);
					mElectricity = 0;
					mFall = false;//重力が発生していない
					mJump = false;//ジャンプしていない
					mFloating = false;//浮遊していない
					//mPos->y = a->Position()->y - mSize->y;
					mPoppedState = true;
					mPos->x = old_x;
					mVelocity->x *= -5.f;
				}
			}
		}
		if (a->Tag() == "Goal")
		{
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				mGoal = true;
			}
		}
		if (a->Tag() == "SmallEnemy")
		{
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				if (mPoppedState)
				{
					Actor::Destroy(a);
				}
				else
				{
					Actor::Destroy(this);
				}
			}
		}
	}
}


bool Player::CheckHit(int x, int y, int width, int height)
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

bool Player::RGoal()
{
	return mGoal;
}


