#include "GamePlay.h"
#include "../Map/Map.h"

Map map;

GamePlay::GamePlay():
	player()
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
	//player.SetPosition(*new Vector2(0,0));
	//map.Init("../Assets/Data/map.csv");
}

void GamePlay::Update()
{
	player.Update();
	//map.Update();
}

void GamePlay::Draw()
{
	player.Draw();
	//map.Draw();
}
