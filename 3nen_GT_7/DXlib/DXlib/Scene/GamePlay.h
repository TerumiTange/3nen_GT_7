#pragma once
#include "../Device/Dx.h"

#include "../Actor/Player.h"

class GamePlay
{
public:
	GamePlay();
	~GamePlay();
	void Init();
	void Update();
	void Draw();

private:
	Player player;
};