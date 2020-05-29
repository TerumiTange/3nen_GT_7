#include "RushEnemy.h"
#include "ActorManager.h"
#include "Player.h"
#include "../Collider//ComponentManager.h"

RushEnemy::RushEnemy(const Vector2 & pos, const char * tag) :
	Actor(tag),
	mCollider(new ColliderComponent(this)),
	mPos(new Vector2(0, 0)),//ポジション
	mSize(new Vector2(32, 32)),//サイズ
	mFilename(tag),//
	mRenderer(new Renderer("Enemy3")),//アイドル状態の画像
	mFall(false),//重力
	mRight(true),
	mStalker(false),//追跡状態か？
	staSize(200),//追跡範囲
	sRenderer(new Renderer("Enemy3")),//追跡状態の画像
	paralRenderer(new Renderer("ThunderEffect")),//マヒ状態の画像
	speed(250.0f),//速度
	paraTime(4.0f),//マヒ時間
	paralimitTime(new CountDownTimer()),//マヒ時間のタイマー
	paral(false),//マヒ状態か？
	playerHitTimer(new CountDownTimer()),//プレイヤーとの連続ヒットを防ぐため（これがないとあたった瞬間に死ぬ）
	paralimitTimer(new CountDownTimer()), //連続で麻痺状態にならないためのタイマー
	sound(new Sound()),
	atTime(2.0f),
	attackTimer(new CountDownTimer(0.0f)),
	rush(false),
	mUpTimer(new CountUpTimer())
{
	*mPos = pos;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
	sound->Init();
	sound->Load("./Assets/Sound/deth.wav");
	sound->Load("./Assets/Sound/paral.wav");
}

RushEnemy::~RushEnemy() = default;

void RushEnemy::End()
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
	delete(attackTimer);
	delete(mUpTimer);
}

void RushEnemy::Update()
{
	playerHitTimer->Update();
	paralimitTimer->Update();
	mUpTimer->Update();
	Paralise();

	if (direction.x < 0) mRight = false;
	else if (direction.x > 0) mRight = true;

	if (!paral)
	{
		Rush();
	}
}

void RushEnemy::Draw()
{
	//マヒ状態での描画
	if (paral)
	{
		int a = fmod(mUpTimer->Now() * 3, 2);
		mRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), a, *mSize, FALSE);
		paralRenderer->Draw(mPos->x - 16, mPos->y + 32);
		return;
	}

	//アイドル状態での描画
	if (!mStalker)
	{
		int t = fmod(mUpTimer->Now() * 3, 1);
		mRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), t, *mSize, FALSE);
	}
	//追跡状態での描画
	if (mStalker)
	{
		//追跡左向き
		if (!mRight)
		{
			int r = fmod(mUpTimer->Now() * 3, 1);
			sRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), r, *mSize, FALSE);
		}
		//追跡左向き
		else if (mRight)
		{
			int l = fmod(mUpTimer->Now() * 3, 1);
			sRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), l, *mSize, TRUE);
		}
	}
}

void RushEnemy::Hit()
{
	for (auto && hit : mCollider->onCollisionStay())
	{
		auto cPosX = hit->getOwner()->Position()->x;
		auto cPosY = hit->getOwner()->Position()->y;
		auto cSizeX = hit->getOwner()->Size()->x;
		auto cSizeY = hit->getOwner()->Size()->y;

		if (hit->getOwner()->Tag() == "Wall")
		{
			if (old_y < cPosY)//自分が上
			{
				mPos->y = cPosY - mSize->y;
			}
			else if (old_y > cPosY)//自分がした
			{
				mPos->y = cPosY + cSizeY + 1;
			}
			else if (old_x < cPosX)//自分が左
			{
				mPos->x = cPosX - mSize->x;
			}
			else if (old_x > cPosX)//自分が右
			{
				mPos->x = cPosX + mSize->x;
			}
		}
	}

	for (auto && hit : mCollider->onCollisionEnter())
	{
		auto cPosX = hit->getOwner()->Position()->x;
		auto cPosY = hit->getOwner()->Position()->y;
		auto cSizeX = hit->getOwner()->Size()->x;
		auto cSizeY = hit->getOwner()->Size()->y;

		if (hit->getOwner()->Tag() == "Wall")
		{
			if (old_y < cPosY)//自分が上
			{
				mPos->y = cPosY - mSize->y;
			}
			else if (old_y > cPosY)//自分が下
			{
				mPos->y = cPosY + cSizeY;
			}
			else if (old_x < cPosX)//自分が左
			{
				mPos->x = cPosX - mSize->x;
			}
			else if (old_x > cPosX)//自分が右
			{
				mPos->x = cPosX + mSize->x + 1;
			}
		}
	}
}

void RushEnemy::ToPlayer()
{
	//プレイヤーが一定範囲にはいったらaqrt
	if (std::sqrtf(std::powf(pPos.x - mPos->x, 2) + std::powf(pPos.y - mPos->y, 2)) < staSize)
	{
		mStalker = true;
	}
}

void RushEnemy::Rush()
{
	pPos = GetActorManager()->GetPlayer()->GetPosition();
	ToPlayer();
	//追跡状態でマヒ状態でなければ
	if (mStalker && !paral)
	{
		attackTimer->Update();

		if (attackTimer->IsTime())
		{
			psPos = pPos;
			Actor::SetPos(*mPos);
			old_x = mPos->x;
			old_y = mPos->y;
			direction.x = psPos.x - old_x;
			direction.y = psPos.y - old_y;
			direction.normalize();

			mPos->x += direction.x*speed;
			mPos->y += direction.y*speed;

			attackTimer->SetTime(atTime);
		}
	}
}

void RushEnemy::Paralise()
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
