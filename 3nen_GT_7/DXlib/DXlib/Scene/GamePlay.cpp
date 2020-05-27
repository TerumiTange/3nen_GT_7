#include "GamePlay.h"
#include "../Actor/Actor.h"
#include "../Actor/Player.h"
#include "../Actor/ActorManager.h"
#include "../Collider/Collider.h"
#include "../Collider/Physics.h"
#include "../Map/Map.h"
#include "../Actor/Enemy.h"
#include "../Utility/Vector2.h"
#include "Load.h"

#include "SceneManager.h"

#include <thread>

#define SAFE_DELETE(x) if(x){delete x; x=0;}

GamePlay::GamePlay(ISceneChanger* changer, const char* sname) :
	BaseScene(changer),
	mActorManager(new ActorManager()),
	//sound(new Sound()),
	input(new Input()),
	mStageName(sname),
	pose(false),
	mInputTimers(new CountDownTimer()),
	mRenderer(new Renderer("Number")),
	mPhysics(new Physics())
{
	Actor::SetActorManager(mActorManager);
	Collider::setPhysics(mPhysics);
}

GamePlay::~GamePlay()
{
	mActorManager->End();
	mActorManager->Clear();
	delete(mActorManager);
	delete(input);
	delete(mInputTimers);
	delete(mRenderer);

	//sound->StopBGM("./Assets/Sound/GamePlay.mp3");
	SceneManager::sound->StopBGM("./Assets/Sound/GamePlay.mp3");
	//sound->Init();
	//delete(sound);
	SceneManager::mCamera->Init(Vector2(0, 0));//カメラを初期位置にしておく
	mPhysics->clear();
	delete(mPhysics);
	//なぜかColliderのPhysicsがいきているから
	Collider::setPhysics(nullptr);
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
	mActorManager->Clear();
	mPhysics->clear();
	SceneManager::gameClear = false;
	SceneManager::score = 0;
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
	//new Player(Vector2(50, 50));

	Map* map = new Map();
	map->Init(mStageName);
	delete(map);

	//マップの後にエネミーを実装すること
	Enemy* enemy = new Enemy();
	if (mStageName == "stage1")
	{
		enemy->InitM("./Assets/Data/EnemyList1.csv");
	}
	else if (mStageName == "stage2")
	{
		enemy->InitM("./Assets/Data/EnemyList2.csv");
	}
	else if (mStageName == "stage3")
	{
		enemy->InitM("./Assets/Data/EnemyList3.csv");
	}
	else if (mStageName == "stage4")
	{
		enemy->InitM("./Assets/Data/EnemyList4.csv");
	}
	else if (mStageName == "stage5")
	{
		enemy->InitM("./Assets/Data/EnemyList5.csv");
	}
	else//例外処理
	{
		enemy->Init("./Assets/Data/EnemyList.csv");
	}
	//enemy->Init("./Assets/Data/EnemyList.csv");
	mActorManager->SetEnemyCount(enemy->GetEnemyCount());//敵の数をセット
	delete(enemy);
	
	//sound->Init();
	//sound->Load("./Assets/Sound/GamePlay.mp3");//BGM
	//sound->Load("./Assets/Sound/kettei.wav");
	input->Init();
	input->JoyInit();
	SceneManager::mCamera->Init(Vector2(0, 0));
	pose = false;
	SceneManager::mElapsedTime->Init();
	if (!mActorManager->GetPlayer())//プレイヤーがいなければ
	{
		new Player(Vector2(50, 50));
	}
	SceneManager::mCamera->Init(mActorManager->GetPlayer()->GetPosition());//カメラの位置
	SceneManager::mCamera->Update();//一回同期させる
}

void GamePlay::Update()
{
	input->JoyUpdate();//ポーズ中でもコントローラーをいじれるように
	mInputTimers->Update();//操作遅延用	
	
	//DrawFormatString(500, 0, Cr, "%d:%0.2f", SceneManager::mElapsedTime->Now(), SceneManager::mElapsedTime->Rate() - int(SceneManager::mElapsedTime->Rate()));
	//DrawFormatString(500, 0, Cr, "%d", int(SceneManager::mElapsedTime->Now()));
	if (pose)//ポーズ中
	{
		if (mInputTimers->IsTime())
		{
			if (input->PadDown(JoyCode::Joy_Start) || input->GetKeyDown(P))
			{
				//sound->PlaySE("./Assets/Sound/kettei.wav");
				SceneManager::sound->PlaySE("./Assets/Sound/kettei.wav");
				pose = false;
				mInputTimers->SetTime(0.3f);
			}
			if (input->PadDown(JoyCode::Joy_X) || input->GetKeyDown(R))
			{
				//sound->PlaySE("./Assets/Sound/kettei.wav");
				SceneManager::sound->PlaySE("./Assets/Sound/kettei.wav");
				Reset();
			}
			if (input->PadDown(JoyCode::Joy_Back) || input->GetKeyDown(B))
			{
				//sound->PlaySE("./Assets/Sound/kettei.wav");
				SceneManager::sound->PlaySE("./Assets/Sound/kettei.wav");
				NextScene();
			}
		}
	}
	else//ポーズでないなら
	{
		SceneManager::mElapsedTime->Update();//時間を更新
		mActorManager->Update();
		mPhysics->sweepAndPrune();//当たり判定
		mActorManager->Hit();//当たり判定処理

		if (mActorManager->GetPlayer())
		{
			SceneManager::mCamera->GetPPos(mActorManager->GetPlayer()->GetPosition());
			SceneManager::mCamera->Update();
			if (mStageName == "map")
			{
				SceneManager::mCamera->CameraPos.y -= 32;
			}
		}
		//sound->PlayBGM("./Assets/Sound/GamePlay.mp3");
		SceneManager::sound->PlayBGM("./Assets/Sound/GamePlay.mp3");

		if (!mActorManager->GetPlayer())//プレイヤーが死んでいたら
		{
			//リセット
			//Reset();

			NextScene();
		}

		if (mActorManager->GetEnemyCount() == 0)//敵をすべて倒した
		{
			SceneManager::gameClear = true;
			SceneManager::score += 500;//クリアボーナス500点追加
			NextScene();
		}

		if (mInputTimers->IsTime())
		{
			if (input->GetKeyDown(P) || input->PadDown(Joy_Start))
			{
				//sound->PlaySE("./Assets/Sound/kettei.wav");
				SceneManager::sound->PlaySE("./Assets/Sound/kettei.wav");
				pose = true;
				mInputTimers->SetTime(0.3f);
			}
		}
	}

}

void GamePlay::Draw()
{
	mActorManager->Draw();
	mRenderer->DrawNumber(Vector2(500, 0), SceneManager::mElapsedTime->Now());

	if (pose)
	{
		int Cr = GetColor(255, 123, 123);
		SetFontSize(32);
		DrawString(300, 100, "ポーズ中 ", Cr);
		DrawString(300, 180, "ゲームに戻る　START ", Cr);
		DrawString(300, 260, "リセット　　　 X    ", Cr);
		DrawString(300, 340, "終了　　　　　BACK  ", Cr);
	}
}

void GamePlay::NextScene()
{
	mSceneChanger->ChangeScene(SceneEnding);
}

void GamePlay::Reset()
{
	mActorManager->End();
	mActorManager->Clear();
	//sound->StopBGM("./Assets/Sound/a.mp3");
	SceneManager::sound->StopBGM("./Assets/Sound/a.mp3");
	Init();
}
