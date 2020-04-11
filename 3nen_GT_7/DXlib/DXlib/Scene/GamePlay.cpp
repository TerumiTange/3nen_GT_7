#include "GamePlay.h"


GamePlay::GamePlay(ISceneChanger* changer):
	BaseScene(changer),
	player(*new Vector2(0,0)),
	map(),
	sound(),
	input(new Input()),
	load(new Load())
{
}

GamePlay::~GamePlay()
{
	sound.StopBGM("./Assets/Sound/a.mp3");
	sound.Init();
}

void GamePlay::Init()
{
	load->Start();
	player.SetPosition(*new Vector2(30,30));
	load->Loading();
	map.Init("./Assets/Data/map.csv");
	load->Loading();
	sound.Init();
	load->Loading();
	sound.Load("./Assets/Sound/a.mp3");
	load->Loading();
	input->Init();
	load->End();
}

void GamePlay::Update()
{
	player.Update();
	//map.Update();
	sound.PlayBGM("./Assets/Sound/a.mp3");
	if (input->GetKeyDown(B))
	{
		NextScene();
	}
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
