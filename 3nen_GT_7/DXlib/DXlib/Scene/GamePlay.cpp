#include "GamePlay.h"
#include "../Actor/Actor.h"
#include "../Actor/Player.h"
#include "../Actor/ActorManager.h"
#include "../Map/Map.h"
#include "../Actor/SmallEnemy.h"
#include "../Utility/Vector2.h"

GamePlay::GamePlay(ISceneChanger* changer) :
	BaseScene(changer),
	mActorManager(new ActorManager()),
	sound(),
	input(new Input())
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
	//Player* player = new Player(Vector2(50, 50));
	new SmallEnemy(*new Vector2(500,50));
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
	mActorManager->Hit();
	sound.PlayBGM("./Assets/Sound/a.mp3");
	if (input->GetKeyDown(B))
	{
		NextScene();
	}

	if (!mActorManager->GetPlayer())//プレイヤーが死んでいたら
	{
		//リセット
		mActorManager->Clear();
		sound.StopBGM("./Assets/Sound/a.mp3");
		Init();
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
