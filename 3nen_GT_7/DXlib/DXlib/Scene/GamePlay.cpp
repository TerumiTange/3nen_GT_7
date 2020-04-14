#include "GamePlay.h"
#include "../Actor/Actor.h"
#include "../Actor/Player.h"
#include "../Actor/ActorManager.h"
#include "../Map/Map.h"

GamePlay::GamePlay(ISceneChanger* changer):
	BaseScene(changer),
	mActorManager(new ActorManager()),
	sound(),
	input(new Input()),
	load(new Load())
{
	Actor::SetActorManager(mActorManager);
}

GamePlay::~GamePlay()
{
	delete(mActorManager);
	sound.StopBGM("./Assets/Sound/a.mp3");
	sound.Init();
}

void GamePlay::Init()
{
	new Player(Vector2(50, 50));
	//load->Start();
	//load->Loading();
	//load->End();
	Map* map = new Map();
	map->Init("./Assets/Data/map.csv");
	delete(map);
	sound.Init();
	sound.Load("./Assets/Sound/a.mp3");
	input->Init();
}

void GamePlay::Update()
{
	mActorManager->Update();
	sound.PlayBGM("./Assets/Sound/a.mp3");
	if (input->GetKeyDown(B))
	{
		NextScene();
	}

	if (!mActorManager->GetPlayer())
	{
		//ƒvƒŒƒCƒ„[‚ªŽ€‚ñ‚Å‚¢‚½‚ç
	}
	if (input->GetKeyDown(R))
	{
		mActorManager->Clear();
		sound.StopBGM("./Assets/Sound/a.mp3");
		Init();
	}
}

void GamePlay::Draw()
{
	mActorManager->Draw();
}

void GamePlay::NextScene()
{
	mSceneChanger->ChangeScene(SceneEnding);
}
