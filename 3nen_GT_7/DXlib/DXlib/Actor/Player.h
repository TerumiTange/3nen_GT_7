
#pragma once
#include "../System/Input.h"
#include "../Utility/Vector2.h"
#include "../Device/Renderer.h"
#include "Collider.h"

enum Type
{
	Top,    //è„
	Under,	//â∫
	Right,	//âE
	Left	//ç∂
};

class Player
{
public :
	Player(const char* tag = "a");
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
	Renderer renderer;
	Input* input;

private:
	//Collider* mCollider;
};