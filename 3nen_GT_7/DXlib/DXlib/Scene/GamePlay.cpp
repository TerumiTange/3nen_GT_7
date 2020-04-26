#include "GamePlay.h"
#include "../Actor/Actor.h"
#include "../Actor/Player.h"
#include "../Actor/ActorManager.h"
#include "../Map/Map.h"
#include "../Actor/Enemy.h"
#include "../Utility/Vector2.h"
#include "Load.h"

#include <thread>

#define SAFE_DELETE(x) if(x){delete x; x=0;}

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
	mActorManager->End();
	mActorManager->Clear();
	delete(mActorManager);
	delete(input);
	
	sound.StopBGM("./Assets/Sound/a.mp3");
	sound.Init();
}

void do_wark1()
{
	Enemy* enemy = new Enemy();
	enemy->Init("./Assets/Data/EnemyList.csv");
	delete(enemy);
}
void do_wark2()
{
	Map* map = new Map();
	map->Init("./Assets/Data/map.csv");
	delete(map);
}

void GamePlay::Init()
{
	try
	{
		std::thread t1(do_wark1);
		std::thread t2(do_wark2);
		t1.join();
		t2.join();
	}
	catch (std::exception &ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	new Player(Vector2(50, 50));

	/*Map* map = new Map();
	map->Init("./Assets/Data/map.csv");
	delete(map);

	Enemy* enemy = new Enemy();
	enemy->Init("./Assets/Data/EnemyList.csv");
	delete(enemy);*/

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
		mActorManager->End();
		mActorManager->Clear();
		sound.StopBGM("./Assets/Sound/a.mp3");
		Init();
	}
	if (input->GetKeyDown(R))
	{
		mActorManager->End();
		mActorManager->Clear();
		sound.StopBGM("./Assets/Sound/a.mp3");
		Init();
	}
	if (mActorManager->GetPlayer()->RGoal())
	{
		NextScene();
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
