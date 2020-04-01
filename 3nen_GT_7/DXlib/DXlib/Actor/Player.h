#pragma once
#include "../Utility/Vector2.h"
#include "../Device/Renderer.h"
#include "Collider.h"


class Player
{
public :
	Player(const char* tag = "Player");
	Player(const Vector2& position, const char* tag = "Player");
	~Player();
	void Init();
	void Update();
	void Draw();
	void SetPosition(const Vector2& position);
	Vector2& GetPosition();

private:
	Vector2* pos;
	const char* filename;

private:
	Collider* mCollider;
};