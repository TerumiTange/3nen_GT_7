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

GamePlay::GamePlay(ISceneChanger* changer, const char* sname) :
	BaseScene(changer),
	mActorManager(new ActorManager()),
	sound(),
	input(new Input()),
	camera(new Camera2d()),
	mStageName(sname)
{
	Actor::SetActorManager(mActorManager);
}

GamePlay::~GamePlay()
{
	mActorManager->End();
	mActorManager->Clear();
	delete(mActorManager);
	delete(input);
	delete(camera);

	sound.StopBGM("./Assets/Sound/a.mp3");
	sound.Init();
}

/*void do_wark1()
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
}*/

void GamePlay::Init()
{
	//try
	//{
	//	std::thread t1(do_wark1);
	//	std::thread t2(do_wark2);
	//	t1.join();
	//	t2.join();
	//}
	//catch (std::exception &ex)
	//{
	//	std::cerr << ex.what() << std::endl;
	//}
	new Player(Vector2(50, 50));

	Map* map = new Map();
	map->Init(mStageName);
	delete(map);

	Enemy* enemy = new Enemy();
	enemy->Init("./Assets/Data/EnemyList.csv");
	mActorManager->SetEnemyCount(enemy->GetEnemyCount());//“G‚Ì”‚ðƒZƒbƒg
	delete(enemy);

	sound.Init();
	sound.Load("./Assets/Sound/a.mp3");
	input->Init();
	camera->Init(Vector2(0, 0));
}

void GamePlay::Update()
{
	mActorManager->Update();
	printfDx("“G‚Ì”%d", mActorManager->GetEnemyCount());
	mActorManager->Hit();
	if (mActorManager->GetPlayer())
	{
		camera->GetPPos(mActorManager->GetPlayer()->GetPosition());
		camera->Update();
		if (mStageName == "map")
		{
			camera->CameraPos.y -= 32;
		}
	}
	sound.PlayBGM("./Assets/Sound/a.mp3");
	if (input->GetKeyDown(B))
	{
		NextScene();
	}

	if (!mActorManager->GetPlayer())//ƒvƒŒƒCƒ„[‚ªŽ€‚ñ‚Å‚¢‚½‚ç
	{
		//ƒŠƒZƒbƒg
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
	if (mActorManager->GetPlayer()->RGoal() || mActorManager->GetEnemyCount() == 0)//ƒS[ƒ‹‚µ‚½‚Ü‚½‚Í“G‚ð‚·‚×‚Ä“|‚µ‚½
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
