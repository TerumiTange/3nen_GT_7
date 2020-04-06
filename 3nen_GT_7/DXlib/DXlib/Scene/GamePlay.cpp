#include "GamePlay.h"


GamePlay::GamePlay(ISceneChanger* changer):
	BaseScene(changer),
	player(*new Vector2(0,0)),
	map(),
	sound()
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
	player.SetPosition(*new Vector2(30,30));
	map.Init("./Assets/Data/map.csv");
	sound.Init();
	sound.Load("./Assets/Sound/a.mp3");
	
}

void GamePlay::Update()
{
	player.Update();
	//map.Update();
	sound.PlayBGM("./Assets/Sound/a.mp3");
}

void GamePlay::Draw()
{
	player.Draw();
	map.Draw();
}

void GamePlay::NextScene()
{
	mSceneChanger->ChangeScene(SceneEnding);
}
