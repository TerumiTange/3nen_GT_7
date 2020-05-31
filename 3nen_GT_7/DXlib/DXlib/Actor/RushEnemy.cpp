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
	if (GetDeath())return;

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
	if (GetDeath())
	{
		//ここに爆発の描画を
		return;
	}

	//マヒ状態での描画
	if (paral)
	{
		SetDrawBright(255, 0, 0);
		int a = fmod(mUpTimer->Now() * 3, 2);
		mRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), a, *mSize, FALSE);
		SetDrawBright(255, 255, 255);
		paralRenderer->DrawAlternating(mPos->x, mPos->y, 3);
		return;
	}

	//アイドル状態での描画
	if (!mStalker)
	{
		int t = fmod(mUpTimer->Now() * 3, 2);
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

		if (hit->getOwner()->Tag() == "Wall" ||
			hit->getOwner()->Tag() == "FlyEnemy" ||
			hit->getOwner()->Tag() == "RushEnemy" ||
			hit->getOwner()->Tag() == "PatrolEnemy")
		{
			auto cPosX = hit->getOwner()->Position()->x;
			auto cPosY = hit->getOwner()->Position()->y;
			auto cSizeX = hit->getOwner()->Size()->x;
			auto cSizeY = hit->getOwner()->Size()->y;

			auto sx = cPosX + (cSizeX / 2);//真ん中
			auto sy = cPosY + (cSizeY / 2);//真ん中

			Vector2 dir = Vector2(old_x + (mSize->x / 2), mPos->y + (mSize->y / 2)) - Vector2(sx, sy);

			if (abs(dir.x) > abs(dir.y))
			{
				if (dir.x > 0)//相手の右に当たったら
				{
					mPos->x = cPosX + mSize->x + 1;
				}
				else//左に当たったら
				{
					mPos->x = cPosX - mSize->x - 1;
				}
			}
			else
			{
				if (dir.y < 0)//相手の下に当たったら
				{
					if (direction.y > 0)
					{
						mPos->y = cPosY - mSize->y;
						direction.y = 0;
					}
				}
				else//上に当たったら
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
		auto sx = cPosX + (cSizeX / 2);//真ん中
		auto sy = cPosY + (cSizeY / 2);//真ん中
		Vector2 dir = Vector2(mPos->x + (mSize->x / 2), mPos->y + (mSize->y / 2)) - Vector2(sx, sy);

		if (hit->getOwner()->Tag() == "Wall" ||
			hit->getOwner()->Tag() == "FlyEnemy" ||
			hit->getOwner()->Tag() == "RushEnemy" ||
			hit->getOwner()->Tag() == "PatrolEnemy")
		{
			if (abs(dir.x) > abs(dir.y))
			{
				if (dir.x > 0)//相手の右に当たったら
				{
					mPos->x = cPosX + mSize->x;
					if (direction.x < 0)
					{
						direction.x = 0;
					}
				}
				else//左に当たったら
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
				if (dir.y < 0)//相手の下に当たったら
				{
					mPos->y = cPosY - mSize->y;
					if (direction.y > 0)
					{
						mPos->y = cPosY - mSize->y;
					}
				}
				else//上に当たったら
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
