#include "ActorManager.h"
#include "Actor.h"
#include "Player.h"
#include <algorithm>
#include <iterator>

ActorManager::ActorManager():
	mUpdatingActors(false),
	mEnemyCount(0)
{
}

ActorManager::~ActorManager() = default;

void ActorManager::End()
{
	for (auto&& actor : mActors)
	{
		actor->End();
	}
}

void ActorManager::Init()
{
}

void ActorManager::Update()
{
	mUpdatingActors = true;
	for (auto&& actor : mActors)
	{
		actor->update();
	}
	mUpdatingActors = false;

	MovePendingToMain();

	Remove();
}

void ActorManager::Hit()
{
	if (!GetPlayer())return;
	GetPlayer()->Hit(mActors);
	for (auto&& a : mActors)
	{
		//a->Hit(mActors);
		if ((a->Tag() == "SmallEnemy") || (a->Tag() == "FlyEnemy"))
		{
			a->Hit(mActors);
		}
	}
	//for (auto && a : mActors)
	//{
	//	for (auto && b : mActors)
	//	{
	//		if (CheckHit(a->Position()->x, a->Position()->y, a->Size()->x, a->Size()->y, b->Position()->x, b->Position()->y, b->Size()->x, b->Size()->y))
	//		{
	//			a->Hit(b->Tag(), b->Position(), b->Size());
	//		}
	//	}
	//}
	//std::list<std::shared_ptr<Actor>>temp;
	//for (const auto & a : mActors)
	//{
	//	auto itr = std::find()
	//	temp.emplace_back(a);
	//}
}

bool ActorManager::CheckHit(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2)
{
	if (x1 + width1 < x2)return false;
	if (x2 + width2 < x1)return false;
	if (y1 + height1 < y2)return false;
	if (y2 + height2 < y1)return false;
	return true;
	//int L1 = mPos->x;
	//int R1 = mPos->x + mSize->x;
	//int L2 = x;
	//int R2 = x + width;
	//if (R1 < L2)return false;
	//if (R2 < L1)return false;
	//if (mPos->x + mSize->x < x)return false;
	//if (x + width < mPos->x)return false;

	//int U1 = mPos->y;
	//int D1 = mPos->y + mSize->y;
	//int U2 = y;
	//int D2 = y + height;
	//if (D1 < U2)return false;
	//if (D2 < U1)return false;
	//if (mPos->y + mSize->y < y)return false;
	//if (y + height < mPos->y)return false;
	//return true;
	//return false;
}

void ActorManager::Draw()
{
	//for (auto&& actor : mActors)
	//{
	//	actor->Draw();
	//}
	for (auto&& actor : mActors)
	{
		if (actor->Tag() != "Player")
		{
			actor->Draw();
		}
	}
	//プレイヤーを一番前にするため最後に表示する
	GetPlayer()->Draw();
}

void ActorManager::Add(Actor* add)
{
	if (mUpdatingActors) 
	{
		mPendingActors.emplace_back(add);
	}
	else 
	{
		mActors.emplace_back(add);
	}
}

void ActorManager::Clear()
{
	mPendingActors.clear();
	mActors.clear();
}

void ActorManager::SetEnemyCount(size_t e)
{
	mEnemyCount = e;
}

size_t ActorManager::GetEnemyCount()
{
	return mEnemyCount;
}

std::shared_ptr<Player> ActorManager::GetPlayer() const
{
	std::shared_ptr<Player> p = nullptr;
	for (const auto& actor : mActors) 
	{
		p = std::dynamic_pointer_cast<Player>(actor);
		if (p) 
		{
			return p;
		}
	}
	//最後まで見つからなければnullptrを返す
	return p;
}

void ActorManager::Remove()
{
	auto itr = mActors.begin();
	while (itr != mActors.end()) 
	{
		if ((*itr)->GetState() == ActorState::DEAD) {
			if ((*itr)->Tag() != "Player")
			{
				mEnemyCount--;//プレイヤーでなければ減らす
			}
			(*itr)->End();//死んだらメモリ開放
			itr = mActors.erase(itr);
		}
		else 
		{
			++itr;
		}
	}
}

void ActorManager::MovePendingToMain()
{
	if (mPendingActors.empty())
	{
		return;
	}
	std::copy(mPendingActors.begin(), mPendingActors.end(), std::back_inserter(mActors));
	mPendingActors.clear();
}
