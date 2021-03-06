#pragma once
#include "Actor.h"
#include "../Utility/Vector2.h"
#include <memory>
#include <list>

class Actor;
class Player;

class ActorManager
{
public:
	ActorManager();
	~ActorManager();
	void End();
	void Init();
	void Update();
	void Hit();
	void Draw();
	void Add(Actor* add);
	void Clear();
	std::list<std::shared_ptr<Actor>>GetActors();

	void SetEnemyCount(size_t e);
	size_t GetEnemyCount();

	//アクター配列の中からプレイヤーを取得
	std::shared_ptr<Player>GetPlayer() const;
	//一番最初に見つかったActorの取得
	template<typename T>
	std::shared_ptr<T> GetActor()const
	{
		std::shared_ptr<T> actor = nullptr;
		for (const auto& a : mActors)
		{
			actor = std::dynamic_pointer_cast<T>(a);
			if (actor)
			{
				return actor;
			}
		}
		for (const auto & a : mPendingActors)
		{
			actor = std::dynamic_pointer_cast<T>(a);
			if (actor)
			{
				return actor;
			}
		}
		//最後まで見つからなければnullptrを返す
		return actor;
	}

	std::list<std::shared_ptr<Actor>>getActorList();

private:
	void Remove();
	void MovePendingToMain();
	

	ActorManager(const ActorManager&) = delete;
	ActorManager& operator=(const ActorManager&) = delete;

private:
	std::list<std::shared_ptr<Actor>>mActors;
	std::list<std::shared_ptr<Actor>>mPendingActors;
	std::list<std::shared_ptr<Actor>>mParalActors;
	bool mUpdatingActors;
	bool mWallStart;
	size_t mEnemyCount;
	size_t count;
};