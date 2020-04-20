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
	virtual void Hit()override;
	bool CheckHit(int x, int y, int width, int height);
	void HitMap();
	//void HitEnemy();

private:
	Vector2* mPos;
	int mWidth;
	int mHeight;
	const char* mFilename;
	Renderer* mRenderer;
	Input* mInput;
	bool mFall;
private:
	CSVReader* mCSVReader;
	std::vector<int> mCSV;
	int mapWidth;
	int mapHeight;
};