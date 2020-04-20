#pragma once

#include <memory>

enum class ActorState
{
	ACTIVE,//�����Ă�
	DEAD   //����ł�
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

	virtual void Hit() = 0;

	void update();//�S�čX�V�p

	//�A�N�^�[�폜
	static void Destroy(Actor* actor);
	static void Destroy(std::shared_ptr<Actor> actor);

	//�Q�b�^�[�Z�b�^�[
	void SetPos(Vector2& position);
	void SetSize(Vector2& size);
	std::shared_ptr<Vector2> Position()const;
	std::shared_ptr<Vector2>Size()const;
	ActorState GetState() const;
	const char* Tag() const;

	//ActorManager�̓o�^
	static void SetActorManager(ActorManager* manager);
	ActorManager* GetActorManager();

private:
	std::shared_ptr<Vector2> mPos;
	std::shared_ptr<Vector2> mSize;
	ActorState mState;
	const char* mTag;

	static ActorManager* mActorManager;
};