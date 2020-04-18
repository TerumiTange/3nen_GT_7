#pragma once
#include "Actor.h"
#include "../System/Input.h"
#include "../Utility/Vector2.h"
#include "../Device/CSVReader.h"
#include "../Device/Renderer.h"

class Player:
	public Actor
{
public :
	Player(const char* tag = "Player");
	Player(const Vector2& position, const char* tag = "Player");
	~Player();
	void Init();
	virtual void Update()override;
	virtual void Draw() override;
	void SetPosition(const Vector2& position);
	Vector2& GetPosition();
	void Hit();

private:
	Vector2* pos;
	int Width;
	int Height;
	const char* filename;
	Renderer renderer;
	Input* input;
	bool fall;
private:
};