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
	//�v���C���[����ԑO�ɂ��邽�ߍŌ�ɕ\������
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
	//�Ō�܂Ō�����Ȃ����nullptr��Ԃ�
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
				mEnemyCount--;//�v���C���[�łȂ���Ό��炷
			}
			(*itr)->End();//���񂾂烁�����J��
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
