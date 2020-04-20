#pragma once

#include <memory>
#include <list>

class Actor;
class Player;

class ActorManager
{
public:
	ActorManager();
	~ActorManager();
	void Init();
	void Update();
	void Hit();
	void Draw();
	void Add(Actor* add);
	void Clear();

	//�A�N�^�[�z��̒�����v���C���[���擾
	std::shared_ptr<Player>GetPlayer() const;
	//��ԍŏ��Ɍ�������Actor�̎擾
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
		//�Ō�܂Ō�����Ȃ����nullptr��Ԃ�
		return actor;
	}

private:
	void Remove();
	void MovePendingToMain();

	ActorManager(const ActorManager&) = delete;
	ActorManager& operator=(const ActorManager&) = delete;

private:
	std::list<std::shared_ptr<Actor>>mActors;
	std::list<std::shared_ptr<Actor>>mPendingActors;
	bool mUpdatingActors;
};