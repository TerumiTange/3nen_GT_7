#include "PatrolEnemy.h"
#include "ActorManager.h"
#include "Player.h"
#include "../Collider//ComponentManager.h"

PatrolEnemy::PatrolEnemy(const Vector2 & pos, const Vector2 & patpos1, const Vector2 & patpos2, const Vector2 & patpos3, const Vector2 & patpos4, const char * tag) :
	Actor(tag),
	mCollider(new ColliderComponent(this)),
	mPos(new Vector2(0, 0)),//ポジション
	mSize(new Vector2(32, 32)),//サイズ
	mFilename(tag),//
	mRenderer(new Renderer("Enemy2IDL")),//アイドル状態の画像
	mFall(false),//重力
	mRight(true),
	mStalker(false),//追跡状態か？
	staSize(120),//追跡範囲
	sRenderer(new Renderer("EnemyMove")),//追跡状態の画像
	paralRenderer(new Renderer("ThunderEffect")),//マヒ状態の画像
	speed(6.0f),//速度
	paraTime(3.0f),//マヒ時間
	paralimitTime(new CountDownTimer()),//マヒ時間のタイマー
	paral(false),//マヒ状態か？
	playerHitTimer(new CountDownTimer()),//プレイヤーとの連続ヒットを防ぐため（これがないとあたった瞬間に死ぬ）
	paralimitTimer(new CountDownTimer()), //連続で麻痺状態にならないためのタイマー
	sound(new Sound()),
	patrolPos(0),
	mPatrol(false),//巡回状態か？
	/*pspeed(5.0f),//巡回速度*/
	bomRenderer(new Renderer("BOMEFFECT")),
	pspeed(8.0f),//巡回速度
	mUpTimer(new CountUpTimer()),
	deathUpTimer(new CountUpTimer()),
	removeS(6.0f)//追跡後の速度
{
	*mPos = pos;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
	sound->Init();
	sound->Load("./Assets/Sound/deth.wav");
	sound->Load("./Assets/Sound/paral.wav");
	sound->Load("./Assets/Sound/paral2.wav");
	sound->Load("./Assets/Sound/electric.wav");

	//巡回のポジション
	patrolPos.push_back(Vector2(patpos1.x, patpos1.y));//1位置
	patrolPos.push_back(Vector2(patpos2.x, patpos2.y));//2位置
	patrolPos.push_back(Vector2(patpos3.x, patpos3.y));//3位置
	patrolPos.push_back(Vector2(patpos4.x, patpos4.y));//4位置
	patrolPos.push_back(Vector2(pos));//追跡後に戻る位置
}

PatrolEnemy::~PatrolEnemy() = default;

void PatrolEnemy::End()
{
	sound->DeleteM("./Assets/Sound/deth.wav");
	sound->DeleteM("./Assets/Sound/paral.wav");
	sound->DeleteM("./Assets/Sound/paral2.wav");
	sound->DeleteM("./Assets/Sound/electric.wav");
	delete(mPos);
	delete(mSize);
	delete(mRenderer);

	delete(sRenderer);
	delete(paralRenderer);
	delete(paralimitTime);
	delete(paralimitTimer);
	delete(playerHitTimer);
	delete(sound);
	delete(mUpTimer);
	delete(bomRenderer);
	delete(deathUpTimer);

	patrolPos.clear();
}

void PatrolEnemy::Update()
{
	if (GetDeath())return;

	if (GetDeath())return;
	playerHitTimer->Update();
	paralimitTimer->Update();
	mUpTimer->Update();
	Paralise();

	if (direction.x < 0) mRight = false;
	else if (direction.x > 0) mRight = true;

	if (!paral)//マヒ状態でないなら
	{
		sound->StopBGM("./Assets/Sound/electric.wav");
		Move();
		Patrol();
		return;
	}
	sound->PlaySEF("./Assets/Sound/electric.wav");
}

void PatrolEnemy::DeathUpdate()
{
	deathUpTimer->Update();
}

void PatrolEnemy::Draw()
{	
	if (GetDeath())
	{
		sound->PlaySEF("./Assets/Sound/deth.wav");
		DeathUpdate();
		int d = fmod(deathUpTimer->Now() * 5, 9);
		bomRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), d, *mSize, FALSE);
		return;
	}

	//マヒ状態での描画
	if (paral)
	{
		SetDrawBright(255, 0, 0);
		int a = fmod(mUpTimer->Now() * 3, 1);
		sRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), a, *mSize, FALSE);
		SetDrawBright(255, 255, 255);
		int b = fmod(mUpTimer->Now() * 10, 5);
		paralRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), b, *mSize, FALSE);
		return;
	}

	//アイドル状態での描画
	if (!mStalker)
	{
		int t = fmod(mUpTimer->Now() * 3, 4);
		mRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), t, *mSize, FALSE);
	}
	//追跡状態での描画
	if (mStalker)
	{
		//追跡左向き
		if (!mRight)
		{
			int r = fmod(mUpTimer->Now() * 3, 4);
			sRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), r, *mSize, FALSE);
		}
		//追跡左向き
		else if (mRight)
		{
			int l = fmod(mUpTimer->Now() * 3, 4);
			sRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), l, *mSize, TRUE);
		}
	}
}

void PatrolEnemy::Hit()
{
	for (auto && hit : mCollider->onCollisionEnter())
	{
		if (hit->getOwner()->GetElectricShock())
		{
			SetElectricShock(true);
		}
		//if (hit->getOwner()->Tag() == "Wall" ||
		//	hit->getOwner()->Tag() == "FlyEnemy" ||
		//	hit->getOwner()->Tag() == "RushEnemy" ||
		//	hit->getOwner()->Tag() == "PatrolEnemy")
		//{
		//	if (hit->getEnable())
		//	{
		//		SetElectricShock(true);
		//	}
		//}
	}
	//for (auto && hit : mCollider->onCollisionStay())
	//{

	//	if (hit->getOwner()->Tag() == "Wall" ||
	//		hit->getOwner()->Tag() == "FlyEnemy" ||
	//		hit->getOwner()->Tag() == "RushEnemy" ||
	//		hit->getOwner()->Tag() == "PatrolEnemy")
	//	{
	//		auto cPosX = hit->getOwner()->Position()->x;
	//		auto cPosY = hit->getOwner()->Position()->y;
	//		auto cSizeX = hit->getOwner()->Size()->x;
	//		auto cSizeY = hit->getOwner()->Size()->y;

	//		auto sx = cPosX + (cSizeX / 2);//真ん中
	//		auto sy = cPosY + (cSizeY / 2);//真ん中

	//		Vector2 dir = Vector2(old_x + (mSize->x / 2), mPos->y + (mSize->y / 2)) - Vector2(sx, sy);

	//		if (abs(dir.x) > abs(dir.y))
	//		{
	//			if (dir.x > 0)//相手の右に当たったら
	//			{
	//				mPos->x = cPosX + mSize->x + 1;
	//			}
	//			else//左に当たったら
	//			{
	//				mPos->x = cPosX - mSize->x - 1;
	//			}
	//		}
	//		else
	//		{
	//			if (dir.y < 0)//相手の下に当たったら
	//			{
	//				if (direction.y > 0)
	//				{
	//					mPos->y = cPosY - mSize->y;
	//					direction.y = 0;
	//				}
	//			}
	//			else//上に当たったら
	//			{
	//				mPos->y = cPosY + cSizeY + 1;
	//				if (direction.y < 0)
	//				{
	//					direction.y = 0;
	//				}
	//			}
	//		}
	//	}
	//}

	//for (auto && hit : mCollider->onCollisionEnter())
	//{
	//	auto cPosX = hit->getOwner()->Position()->x;
	//	auto cPosY = hit->getOwner()->Position()->y;
	//	auto cSizeX = hit->getOwner()->Size()->x;
	//	auto cSizeY = hit->getOwner()->Size()->y;
	//	auto sx = cPosX + (cSizeX / 2);//真ん中
	//	auto sy = cPosY + (cSizeY / 2);//真ん中
	//	Vector2 dir = Vector2(mPos->x + (mSize->x / 2), mPos->y + (mSize->y / 2)) - Vector2(sx, sy);

	//	if (hit->getOwner()->Tag() == "Wall" ||
	//		hit->getOwner()->Tag() == "FlyEnemy" ||
	//		hit->getOwner()->Tag() == "RushEnemy" ||
	//		hit->getOwner()->Tag() == "PatrolEnemy")
	//	{
	//		if (abs(dir.x) > abs(dir.y))
	//		{
	//			if (dir.x > 0)//相手の右に当たったら
	//			{
	//				mPos->x = cPosX + mSize->x;
	//				if (direction.x < 0)
	//				{
	//					direction.x = 0;
	//				}
	//			}
	//			else//左に当たったら
	//			{
	//				mPos->x = cPosX - mSize->x;
	//				if (direction.x < 0)
	//				{
	//					direction.x = 0;
	//				}
	//			}
	//		}
	//		else
	//		{
	//			if (dir.y < 0)//相手の下に当たったら
	//			{
	//				mPos->y = cPosY - mSize->y;
	//				if (direction.y > 0)
	//				{
	//					mPos->y = cPosY - mSize->y;
	//				}
	//			}
	//			else//上に当たったら
	//			{
	//				mPos->y = cPosY + cSizeY + 1;
	//				if (direction.y < 0)
	//				{
	//					direction.y = 0;
	//				}
	//			}
	//		}
	//	}
	//}
}

void PatrolEnemy::ToPlayer()
{
	//プレイヤーが一定範囲にはいったらaqrt
	if (std::sqrtf(std::powf(pPos.x - mPos->x, 2) + std::powf(pPos.y - mPos->y, 2)) < staSize)
	{
		mStalker = true;
		mPatrol = false;
	}
	else
	{
		mStalker = false;
	}
}
void PatrolEnemy::Move()
{
	pPos = GetActorManager()->GetPlayer()->GetPosition();
	ToPlayer();
	//追跡状態でマヒ状態でなければ
	if (mStalker && !paral)
	{
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

void PatrolEnemy::Paralise()//麻痺状態の処理
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

void PatrolEnemy::Patrol()
{
	if (mPatrol)
	{
		switch (patrolcount)
		{
		case 0:
			PatrolMove();

			if (old_x >= a.x && old_y <= a.y)
			{
				patrolcount = 1;
			}
			break;

		case 1:
			PatrolMove();

			if (old_x >= a.x && old_y >= a.y)
			{
				patrolcount = 2;
			}
			break;

		case 2:
			PatrolMove();

			if (old_x <= a.x && old_y >= a.y)
			{
				patrolcount = 3;
			}
			break;

		case 3:
			PatrolMove();

			if (old_x <= a.x && old_y <= a.y)
			{
				patrolcount = 0;
			}
			break;
		}
	}

	if (!mStalker && !mPatrol)
	{
		patrolcount = 4;

		old_x = mPos->x;
		old_y = mPos->y;
		a = patrolPos[patrolcount];
		direction.x = a.x - old_x;
		direction.y = a.y - old_y;
		direction.normalize();

		mPos->x += direction.x*removeS;
		mPos->y += direction.y*removeS;

		if (old_x <= a.x && old_y <= a.y)
		{
			mPatrol = true;
			patrolcount = 0;
		}
	}
}

void PatrolEnemy::PatrolMove()
{
	old_x = mPos->x;
	old_y = mPos->y;
	a = patrolPos[patrolcount];
	direction.x = a.x - old_x;
	direction.y = a.y - old_y;
	direction.normalize();

	mPos->x += direction.x*pspeed;
	mPos->y += direction.y*pspeed;
}