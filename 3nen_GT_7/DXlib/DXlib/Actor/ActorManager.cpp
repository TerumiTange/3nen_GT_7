#include "ActorManager.h"
#include "Actor.h"
#include "Player.h"
#include "../Device/Camera2d.h"
#include <algorithm>
#include <iterator>

ActorManager::ActorManager():
	mUpdatingActors(false),
	mEnemyCount(0),
	mWallStart(false),
	count(0)
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
		if (actor->GetElectricShock())mParalActors.emplace_back(actor);
	}
	mUpdatingActors = false;

	MovePendingToMain();

	Remove();


	if (!GetPlayer())return;
	if (count >= 5)
	{
		GetPlayer()->Recovery(); 
		count -= 5;
	}
}

void ActorManager::Hit()
{
	//if (!GetPlayer())return;
	//GetPlayer()->Hit(mActors);
	//for (auto&& a : mActors)
	//{
	//	//a->Hit(mActors);
	//	if ((a->Tag() == "SmallEnemy") || (a->Tag() == "FlyEnemy"))
	//	{
	//		a->Hit(mActors);
	//	}
	//}
	for (auto && a : mActors)
	{
		a->Hit();
	}
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
	//for (size_t i = 0; i < mParalActors.size(); ++i)
	//{
	//	auto a = mParalActors.back()->Position();
	//	for (size_t j = i + 1; j < mParalActors.size(); ++j)
	//	{
	//		auto c = Camera2d::CameraPos;
	//		auto b = mParalActors.front()->Position();
	//		DrawLine(a->x-c.x, a->y - c.y, b->x - c.x, b->y - c.y, GetColor(255, 255, 0));
	//	}
	//}
	
	for (auto && pa : mParalActors)
	{
		auto c = Camera2d::CameraPos;
		auto a = mParalActors.front()->Position();
		DrawLine(a->x - c.x, a->y - c.y, pa->Position()->x + 16 - c.x, pa->Position()->y + 16 - c.y, GetColor(255, 255, 0));
	}
	mParalActors.clear();
	if (!GetPlayer())return;
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

std::list<std::shared_ptr<Actor>> ActorManager::GetActors()
{
	return mActors;
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
			if ((*itr)->Tag() != "Player" && (*itr)->Tag() != "Wall")
			{
				mEnemyCount--;//プレイヤーでなければ減らす
				count++;
				SceneManager::score += 50;
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

std::list<std::shared_ptr<Actor>> ActorManager::getActorList()
{
	return mActors;
}
