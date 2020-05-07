#include "Player.h"
#include "../Device/WindowSize.h"
#include "../Map/Map.h"
#include <algorithm>
#define NOMINMAX
#define max(a,b)            (((a) > (b)) ? (a) : (b))


Player::Player(const Vector2& position, const char* tag):
	Actor(tag),
	mMaxHp(4),										  //最大体力
	mHp(4),											  //現在の体力
	mInvincibleTime(4),								  //無敵時間
	mGoal(false),									  //ゴールしたかどうか
	mPos(new Vector2(0,0)),							  //現在の位置
	mVelocity(new Vector2(0, 0)),					  //移動量
	maxSpeed(7),									  //最大スピード
	mAcceleration(0.5),								  //加速度
	mSize(new Vector2(64, 64)),						  //自分の大きさ
    mFilename(tag),									  //画像名
	mRenderer(new Renderer(tag)),					  //描画関数
	mStaticElectricity(new Renderer("ThunderEffect")),//静電気の画像
	mInput(new Input()),							  //キー入力関数
	mCountTimer(new CountDownTimer()),				  //無敵時間更新カウントダウンタイマー
	mFall(true),									  //落ちているかどうか
	mGravity(16),									  //重力のスピード
	mMovingFastGravity(8),							  //高速移動中の重力
	mMovingFast(false),								  //高速移動しているかどうか
	mMovingFastCount(1),							  //高速移動できる回数
	mMovingFastMaxCount(1),							  //最大高速移動の回数
	mMovingFastTime(0.5f),//0.5f					  //高速移動が回復するまでの時間
	mMovingFastTimer(new CountDownTimer()),			  //高速移動回復用カウントダウンタイマー
	mMovingFastAmount(200),							  //高速移動の移動量
	//mMovingFastDifference(new Vector2(0,0)),		  //高速移動後の位置の差分
	mMovingFastDifferenceX(0),						  //高速移動後の位置の差分X
	mMovingFastDifferenceY(0),						  //高速移動後の位置の差分Y
	mNowMovingFastTimer(new CountDownTimer()),        //高速移動状態のタイマー
	mNowMovingFast(false)							  //高速移動した瞬間
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
	delete(mCountTimer);

	//delete(mMovingFastDifference);

	delete(mMovingFastTimer);
	delete(mNowMovingFastTimer);
	
	
}

void Player::Update()
{
	if (mMovingFastCount > mMovingFastMaxCount)//最大回数をオーバーしたら
	{
		mMovingFastCount = mMovingFastMaxCount;
	}
	//clsDx();
	printfDx("体力%d", mHp);
	printfDx("無敵時間%.001f", mCountTimer->Now());
	printfDx("瞬間移動できる回数%d", mMovingFastCount);
	printfDx("瞬間移動できるようになるまでの時間%.01f", mMovingFastTimer->Now());
	//printfDx("xの値%.1f", mMovingFastDifferenceX);
	//printfDx("yの値%.1f", mMovingFastDifferenceY);

	if (mHp <= 0)return;

	

	mInput->JoyUpdate();//ジョイパッド更新
	mCountTimer->Update();//無敵時間更新

	if (!mMovingFast)//瞬間移動中でなければ
	{
		mMovingFastTimer->Update();//瞬間移動時間更新
	}
	if ((mMovingFastCount <= 0) && (mMovingFastTimer->IsTime()))
	{
		mFall = true;
		//if (mMovingFast)return;
		mMovingFastCount = 1;
	}
	
	if (mNowMovingFastTimer->IsTime())
	{
		mMovingFast = false;
		mFall = true;
	}

	Actor::SetPos(*mPos);
	old_x = mPos->x;
	old_y = mPos->y;
	Fall();
	mNowMovingFastTimer->Update();
	

	if (mInput->GetKeyDown(SPACE) || mInput->PadDown(Joy_A))
	{
		MovingFast();//瞬間移動
	}

	if (mInput->GetKeyDown(H))
	{
		Recovery();
	}

	Move();

	Movement();
}
void Player::Fall()//重力
{
	if (mMovingFast)
	{
		mPos->y += mMovingFastGravity;
		return;
	}
	if (!mFall)return;
	mPos->y += mGravity;
}
void Player::Move()
{
	if (mMovingFast)return;//瞬間移動中ならリターン
	if ((mInput->Horizontal() < 0) || (mInput->GetKey(A) || mInput->GetKey(LEFTARROW)))//左移動
	{
		mVelocity->x = min(mVelocity->x - mAcceleration, -maxSpeed);
	}
	else if ((mInput->Horizontal() > 0) || (mInput->GetKey(D) || mInput->GetKey(RIGHTARROW)))//右移動
	{
		mVelocity->x = max(mVelocity->x + mAcceleration, maxSpeed);
	}
}

void Player::Movement()//移動処理
{
	mPos->y += mVelocity->y;
	mVelocity->y *= 0.7f;
	mPos->x += mVelocity->x;//移動処理
	mVelocity->x *= 0.9f;//ここで慣性性が出る
	
	if (mNowMovingFast)//高速移動なら慣性0
	{
		mVelocity->x = 0;
		mVelocity->y = 0;
		
		//mMovingFastDifference->x -= mPos->x;
		//mMovingFastDifference->y -= mPos->y;
		mMovingFastDifferenceX -= mPos->x;
		mMovingFastDifferenceY -= mPos->y;
		mNowMovingFast = false;
	}

	//画面外に出た場合位置修正
	if (mPos->x < 32)
	{
		mPos->x = 32;
	}
	if (mPos->x > Map::width * 32 - 32)
	{
		mPos->x = Map::width * 32 - 32;
	}
	if (mPos->y > ScreenHeight)
	{
		mPos->y = ScreenHeight;
	}
	if (mPos->y < Map::height * 32 - ScreenHeight - 32)
	{
		mPos->y = Map::height * 32 - ScreenHeight - 32;
	}

}

void Player::MovingFast()//瞬間移動
{
	if (mMovingFastCount <= 0)return;//0以下ならリターン
	if (mMovingFast)return;//瞬間移動中ならリターン
	if (!mNowMovingFastTimer->IsTime())return;//一定時間たつまで無効
	mMovingFast = true;
	mFall = false;
	mNowMovingFast = true;
	mMovingFastCount--;
	//mMovingFastDifference = mPos;
	mMovingFastDifferenceX = mPos->x;
	mMovingFastDifferenceY = mPos->y;

	if ((mInput->Horizontal() < 0) || (mInput->GetKey(A) || mInput->GetKey(LEFTARROW)))
	{
		mVelocity->x = -mMovingFastAmount;
	}
	else if ((mInput->Horizontal() > 0) || (mInput->GetKey(D) || mInput->GetKey(RIGHTARROW)))
	{
		mVelocity->x = mMovingFastAmount;
	}

	if (mInput->Vertical() < 0 || (mInput->GetKey(W) || mInput->GetKey(UPARROW)))
	{
		mVelocity->y = -mMovingFastAmount;
	}
	else if (mInput->Vertical() > 0 || (mInput->GetKey(S) || mInput->GetKey(DOWNARROW)))
	{
		mVelocity->y = mMovingFastAmount;
	}

	mVelocity->x = mInput->Horizontal()*mMovingFastAmount;
	mVelocity->y = mInput->Vertical()*mMovingFastAmount;

	if (mVelocity->x == 0 && mVelocity->y == 0)//もし入力がなければ右に移動
	{
		mVelocity->x = mMovingFastAmount;
	}

	mMovingFastTimer->SetTime(mMovingFastTime);
	mNowMovingFastTimer->SetTime(0.2f);
}

void Player::Damage()//ダメージ
{
	if (mMovingFast)return;//瞬間移動中なら
	if (mCountTimer->IsTime())
	{
		mHp--;
		mCountTimer->SetTime(mInvincibleTime);
	}

	if (mHp <= 0)
	{
		Destroy(this, 3.f);//3秒後に死亡
	}
}

void Player::Recovery()//体力回復
{
	mHp++;
	if (mMaxHp < mHp)
	{
		mHp = mMaxHp;
	}
}


void Player::Draw()
{
	mRenderer->Draw(*mPos);
	//if (mPoppedState)
	//{
	//	mStaticElectricity->Draw(mPos->x - 16, mPos->y + 32);
	//}
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

Vector2& Player::GetPosition()
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
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				mPos->x = old_x;

			}
		}

		if (a->Tag() == "Floor")
		{
			if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				mFall = false;//重力が発生していない
				mPos->y = a->Position()->y - mSize->y;
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
			if (mMovingFast)//高速移動中であれば
			{
				if (CheckHitF(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
				{
					if (a->GetElectricShock())Destroy(a);
					a->SetElectricShock(true);
					mMovingFastCount++;
				}
			}
			else if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				Damage();
			}
		}

		if (a->Tag() == "FlyEnemy")
		{
			if (mMovingFast)//高速移動中であれば
			{
				if (CheckHitF(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
				{
					if (a->GetElectricShock())Destroy(a);
					a->SetElectricShock(true);
					mMovingFastCount++;
				}
			}
			else if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
			{
				Damage();
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

bool Player::CheckHitF(int x, int y, int width, int height)
{
	//if (mPos->x + mSize->x < x)return false;
	//if (x + width < mPos->x - mMovingFastDifference.x) return false;
	//if (mPos->y + mSize->y < y)return false;
	//if (y + height < mPos->y - mMovingFastDifference.y)return false;

	if (mPos->x + mSize->x < x)return false;
	if (mPos->x - mMovingFastDifferenceX > x + width)return false;
	if (mPos->y > y + height)return false;
	if (y > mPos->y + mSize->y + mMovingFastDifferenceY)return false;
	return true;
}

bool Player::RGoal()
{
	return mGoal;
}

bool Player::GetMovingFast()
{
	return mMovingFast;
}


