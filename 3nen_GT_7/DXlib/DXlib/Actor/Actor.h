#pragma once

#include <memory>

enum class ActorState
{
	ACTIVE,//生きてる
	DEAD   //死んでる
};

class ActorManager;
class Vector2;

class Actor 
{
protected:
	Actor(const char* tag);

public:
	virtual ~Actor();

	virtual void Update() = 0;

	virtual void Draw() = 0;

	void update();//全て更新用

	//アクター削除
	static void Destroy(Actor* actor);
	static void Destroy(std::shared_ptr<Actor> actor);

	//ゲッターセッター
	void SetPos(Vector2& position);
	std::shared_ptr<Vector2> Position()const;
	ActorState GetState() const;
	const char* Tag() const;

	//ActorManagerの登録
	static void SetActorManager(ActorManager* manager);
	ActorManager* GetActorManager();

private:
	std::shared_ptr<Vector2> mPos;
	ActorState mState;
	const char* mTag;

	static ActorManager* mActorManager;
};