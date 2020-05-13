#pragma once
#include <list>
#include <memory>

enum class ActorState
{
	ACTIVE,//�����Ă�
	DEAD   //����ł�
};

class ActorManager;
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

	virtual void Hit(std::list<std::shared_ptr<Actor>>) = 0;
	virtual void Hit(const char* tag, std::shared_ptr<Vector2> pos, std::shared_ptr<Vector2> size) = 0;

	void update();//�S�čX�V�p

	//�A�N�^�[�폜
	static void Destroy(Actor* actor);
	static void Destroy(std::shared_ptr<Actor> actor);
	static void Destroy(Actor* actor, float sec);
	static void Destroy(std::shared_ptr<Actor> actor, float sec);

	//�Q�b�^�[�Z�b�^�[
	void SetPos(Vector2& position);
	void SetSize(Vector2& size);
	std::shared_ptr<Vector2> Position()const;
	std::shared_ptr<Vector2>Size()const;
	ActorState GetState() const;
	const char* Tag() const;
	void SetElectricShock(bool f);
	bool GetElectricShock();

	//ActorManager�̓o�^
	static void SetActorManager(ActorManager* manager);
	ActorManager* GetActorManager();

	static CountDownTimer* mElectricTimer;//��჏�ԗp	

private:
	void DestroyTimer();

private:
	std::shared_ptr<Vector2> mPos;
	std::shared_ptr<Vector2> mSize;
	std::unique_ptr<CountDownTimer> mDestroyTimer;
	ActorState mState;
	const char* mTag;
	bool mElectricShock;

	static ActorManager* mActorManager;
};