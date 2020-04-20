#include "ActorManager.h"
#include "Actor.h"
#include "Player.h"
#include <algorithm>
#include <iterator>

ActorManager::ActorManager():
	mUpdatingActors(false)
{
}

ActorManager::~ActorManager() = default;

void ActorManager::Init()
{
	for (auto&& actor : mActors)
	{
		//actor->Init();
	}
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
	for (auto&& actor : mActors)
	{
		actor->Hit(mActors);
	}
}

void ActorManager::Draw()
{
	for (auto&& actor : mActors)
	{
		actor->Draw();
	}
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
	//ÅŒã‚Ü‚ÅŒ©‚Â‚©‚ç‚È‚¯‚ê‚Înullptr‚ð•Ô‚·
	return p;
}

void ActorManager::Remove()
{
	auto itr = mActors.begin();
	while (itr != mActors.end()) 
	{
		if ((*itr)->GetState() == ActorState::DEAD) {
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
