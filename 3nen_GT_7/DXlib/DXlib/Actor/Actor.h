#pragma once
#include "../Utility/Vector2.h"
#include "../Scene/SceneManager.h"
#include <list>
#include <memory>

enum class ActorState
{
	ACTIVE,//生きてる
	DEAD   //死んでる
};

class ActorManager;
class ComponentManager;
class Vector2;
class CountDownTimer;

class Actor 
{
protected:
	Actor(const char* tag);

public:
	virtual ~Actor();

	virtual void End() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Hit() = 0;

	void update();//全て更新用

	//アクター削除
	static void Destroy(Actor* actor);
	static void Destroy(std::shared_ptr<Actor> actor);
	static void Destroy(Actor* actor, float sec);
	static void Destroy(std::shared_ptr<Actor> actor, float sec);

	//ゲッターセッター
	std::shared_ptr<ComponentManager> componentManager() const;
	void SetPos(Vector2& position);
	void SetSize(Vector2& size);
	std::shared_ptr<Vector2> Position()const;
	std::shared_ptr<Vector2>Size()const;
	ActorState GetState() const;
	const char* Tag() const;
	void SetElectricShock(bool f);
	bool GetElectricShock();
	bool GetDeath();

	//ActorManagerの登録
	static void SetActorManager(ActorManager* manager);
	ActorManager* GetActorManager();

	static CountDownTimer* mElectricTimer;//麻痺状態用	
	

private:
	void DestroyTimer();

private:
	std::shared_ptr<ComponentManager> mComponentManager;
	std::shared_ptr<Vector2> mPos;
	std::shared_ptr<Vector2> mSize;
	std::unique_ptr<CountDownTimer> mDestroyTimer;
	ActorState mState;
	const char* mTag;
	bool mElectricShock;
	bool death;

	static ActorManager* mActorManager;
};