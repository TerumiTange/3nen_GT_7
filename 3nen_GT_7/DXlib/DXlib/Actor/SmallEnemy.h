#pragma once
#include "Actor.h"
#include "../Utility/Vector2.h"
#include "../Device/Renderer.h"
#include "../Collider/ColliderComponent.h"

class SmallEnemy :
	public Actor
{
public:
	SmallEnemy(const Vector2& pos, const char* tag = "SmallEnemy");//SmallEnemy
	~SmallEnemy();
	virtual void End()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void Hit() override;
	bool CheckHit(int x, int y, int width, int height);

private:
	ColliderComponent* mCollider;
	Vector2* mPos;
	Vector2* mSize;
	const char* mFilename;
	Renderer* mRenderer;
	bool mFall;
	bool mRight;//�E�ɐi��ł��邩�ǂ���
	//���̐��l
	int old_x;//1�t���[���O�̈ʒu
	int old_y;//1�t���[���O�̈ʒu
};