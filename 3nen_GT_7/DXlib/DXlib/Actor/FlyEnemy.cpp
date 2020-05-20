#include "FlyEnemy.h"
#include "ActorManager.h"
#include "Player.h"
#include "../Collider/ComponentManager.h"

FlyEnemy::FlyEnemy(const Vector2 & pos, const char * tag) :
	Actor(tag),
	mCollider(new ColliderComponent(this)),
	mPos(new Vector2(0, 0)),
	mSize(new Vector2(32, 32)),
	mFilename(tag),
	mRenderer(new Renderer(tag)),
	mFall(false),
	mRight(true),
	mStalker(false),
	staSize(192),
	sRenderer(new Renderer("StalEnemy")),/*,*/
	paralRenderer(new Renderer("ThunderEffect")),//仮の画像
	speed((1.0f)),
	paraTime(4.0f),//麻痺時間
	paralimitTime(new CountDownTimer()),//麻痺時間のタイマー
	paral(false),//麻痺状態かどうか
	playerHitTimer(new CountDownTimer()),//プレイヤーとの連続ヒットを防ぐため（これがないとあたった瞬間に死ぬ）
	paralimitTimer(new CountDownTimer()), //連続で麻痺状態にならないためのタイマー
	sound(new Sound())
{
	*mPos = pos;
	Actor::SetPos(*mPos);
	Actor::SetSize(*mSize);
	sound->Init();
	sound->Load("./Assets/Sound/deth.wav");
	sound->Load("./Assets/Sound/paral.wav");
	
}

FlyEnemy::~FlyEnemy() = default;

void FlyEnemy::End()
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
}

void FlyEnemy::Update()
{
	playerHitTimer->Update();//
	paralimitTimer->Update();//
	Paralise();//
	if (!paral)//麻痺状態でないなら
	{
		Move();
	}
}

void FlyEnemy::Draw()
{
	//mRenderer->Draw(*mPos);

	//マヒ状態での描画
	if (paral)
	{
		mRenderer->Draw(*mPos);
		paralRenderer->Draw(mPos->x - 16, mPos->y + 32);
		return;
	}

	//アイドル状態での描画
	if (!mStalker)
	{
		mRenderer->Draw(*mPos);
	}
	//追跡状態での描画
	if (mStalker)
	{
		sRenderer->Draw(*mPos);
	}
	
}

void FlyEnemy::Hit()
{
}
void FlyEnemy::ToPlayer()
{
	//プレイヤーが一定範囲にはいったらsqrt
	if (std::sqrtf(std::powf(pPos.x - mPos->x, 2) + std::powf(pPos.y - mPos->y, 2)) < 200)
	{
		mStalker = true;
	}
	else
	{
		mStalker = false;
	}
}
/*
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
				//mPos->x = old_x;
				//if (mRight)mRight = false;
				//else mRight = true;

				if (old_y + mSize->y <= a->Position()->y)//自分の下に当たったとき
				{
					mPos->y = a->Position()->y - mSize->y;
				}
				else if (old_y > a->Position()->y + a->Size()->y)//自分の上に当たったとき
				{
					mPos->y = a->Position()->y + a->Size()->y;
				}
				else if (old_x >= a->Position()->x + a->Size()->x)//自分の左に当たったとき
				{
					mPos->x = a->Position()->x + a->Size()->x + 1;
					mRight = true;
				}

				else if (old_x + mSize->x <= a->Position()->x)//自分の右に当たったとき
				{
					mPos->x = a->Position()->x - mSize->x - 1;
					mRight = false;
				}
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
			if (playerHitTimer->IsTime())//プレイヤーと連続ヒットを防ぐため
			{
				//プレイヤーと普通にぶつかったとき
				if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y))
				{
					if (paral&&playerHitTimer->IsTime())//麻痺状態なら
					{
						//Destroy(this);//自分死亡
						for (auto act : actors)
						{
							if (act->GetElectricShock())
							{
								Destroy(act);//麻痺状態の敵全部死亡
							}
						}
					}
				}
			}

			//プレイヤーが一定範囲内に入ったとき（追跡範囲に入ったとき）
			if (CheckHit2(a->Position()->x - 64, a->Position()->y - 64, a->Size()->x, a->Size()->y, staSize))
			{
				mStalker = true;
				pPos.x = a->Position()->x;
				pPos.y = a->Position()->y;
			}

			//プレイヤーが一定範囲から離れたとき（追跡範囲から出たとき）
			//範囲の大きさに変更が必要な場合連絡を
			if (!CheckHit2(a->Position()->x - 64, a->Position()->y - 64, a->Size()->x, a->Size()->y, staSize))
			{
				mStalker = false;
			}
		}

		if (a->Tag() == "FlyEnemy")
		{
			if (CheckHit2(a->Position()->x - 64, a->Position()->y - 64, a->Size()->x, a->Size()->y, 100))
			{
				if (!a->GetElectricShock() && paral)//自身がマヒ状態で相手がマヒ状態でないなら
				{
					a->SetElectricShock(true);
					//SetElectricShock(true);
					//paralimitTime->SetTime(paraTime);
				}
			}
		}
	}
}

void FlyEnemy::Hit(const char * tag, std::shared_ptr<Vector2> pos, std::shared_ptr<Vector2> size)
{
	if (tag == "Wall")
	{
		if (old_y + mSize->y <= pos->y)//自分の下に当たったとき
		{
			mPos->y = pos->y - mSize->y;
		}
		else if (old_y > pos->y + size->y)//自分の上に当たったとき
		{
			mPos->y = pos->y + size->y;
		}
		else if (old_x >= pos->x + size->x)//自分の左に当たったとき
		{
			mPos->x = pos->x + size->x + 1;
		}

		else if (old_x + mSize->x <= pos->x)//自分の右に当たったとき
		{
			mPos->x = pos->x - mSize->x - 1;
		}
	}

	if (tag == "Player")
	{
		if (playerHitTimer->IsTime())//プレイヤーと連続ヒットを防ぐため
		{
			SetElectricShock(true);
			if (paral)
			{
				Destroy(this);
			}
		}
	}
}
*/
/*
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

bool FlyEnemy::CheckHit2(int x, int y, int width, int height, int p)
{
	if (mPos->x + mSize->x + p < x)return false;
	if (x + width < mPos->x - p) return false;
	if (mPos->y - p > y + height) return false;
	if (mPos->y + width + p < y) return false;
	return true;
}
*/
void FlyEnemy::Move()
{
	pPos = GetActorManager()->GetPlayer()->GetPosition();
	ToPlayer();
	//追いかける状態で麻痺状態でなければ
	if (mStalker && !paral)
	{
		//ここに動く処理を
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

void FlyEnemy::Fall()
{

}

void FlyEnemy::Paralise()//麻痺状態の処理
{
	//if (!paralimitTimer->IsTime() && !paralimitTime->IsTime())
	//{
	//	SetElectricShock(false);
	//}
	//else if (Actor::GetElectricShock())
	//{
	//	paral = true;
	//	Actor::SetElectricShock(false);
	//	paralimitTime->SetTime(paraTime);
	//}
	//if (paral)
	//{
	//	paralimitTime->Update();
	//	if (paralimitTime->IsTime())
	//	{
	//		paral = false;
	//		Actor::SetElectricShock(false);
	//		playerHitTimer->SetTime(0.3f);
	//		paralimitTimer->SetTime(0.2f);
	//	}
	//}
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
