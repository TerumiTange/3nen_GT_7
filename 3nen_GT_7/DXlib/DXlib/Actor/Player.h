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
	void Init(const char* name);
	virtual void Update()override;
	virtual void Draw() override;
	void SetPosition(const Vector2& position);
	Vector2& GetPosition();
	void Hit();
	bool CheckHit(int x, int y, int width, int height);
	void HitMap();
	//void HitEnemy();

private:
	Vector2* pos;
	int Width;
	int Height;
	const char* filename;
	Renderer renderer;
	Input* input;
	bool fall;
private:
	CSVReader* mCSVReader;
	std::vector<int> mCSV;
	int mapWidth;
	int mapHeight;
};