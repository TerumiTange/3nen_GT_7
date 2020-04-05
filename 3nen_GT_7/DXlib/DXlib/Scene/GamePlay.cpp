#include "GamePlay.h"


GamePlay::GamePlay():
	player(*new Vector2(0,0)),
	map()
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
	player.SetPosition(*new Vector2(30,30));
	map.Init("./Assets/Data/map.csv");
}

void GamePlay::Update()
{
	player.Update();
	//map.Update();
}

void GamePlay::Draw()
{
	player.Draw();
	map.Draw();
}
