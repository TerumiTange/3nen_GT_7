#pragma once
#include "../Device/Dx.h"

#include "../Actor/Player.h"
#include "../Map/Map.h"
#include "../Device/Sound.h"

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
	Map map;
	Sound sound;
};