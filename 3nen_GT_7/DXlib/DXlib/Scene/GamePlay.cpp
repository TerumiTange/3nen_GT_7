#include "GamePlay.h"
#include "../Actor/Actor.h"
#include "../Actor/Player.h"
#include "../Actor/ActorManager.h"
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
	sound(new Sound()),
	input(new Input()),
	mStageName(sname),
	pose(false),
	mInputTimers(new CountDownTimer()),
	mRenderer(new Renderer("Number"))
{
	Actor::SetActorManager(mActorManager);
	
}

GamePlay::~GamePlay()
{
	mActorManager->End();
	mActorManager->Clear();
	delete(mActorManager);
	delete(input);
	delete(mInputTimers);
	delete(mRenderer);

	sound->StopBGM("./Assets/Sound/a.mp3");
	sound->Init();
	delete(sound);
	SceneManager::mCamera->Init(Vector2(0, 0));//�J�����������ʒu�ɂ��Ă���
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
	//new Player(Vector2(50, 50));

	Map* map = new Map();
	map->Init(mStageName);
	delete(map);

	//�}�b�v�̌�ɃG�l�~�[���������邱��
	Enemy* enemy = new Enemy();
	if (mStageName == "stage1")
	{
		enemy->Init("./Assets/Data/EnemyList1.csv");
	}
	else if (mStageName == "stage2")
	{
		enemy->Init("./Assets/Data/EnemyList2.csv");
	}
	else if (mStageName == "stage3")
	{
		enemy->Init("./Assets/Data/EnemyList3.csv");
	}
	else if (mStageName == "stage4")
	{
		enemy->Init("./Assets/Data/EnemyList4.csv");
	}
	else if (mStageName == "stage5")
	{
		enemy->Init("./Assets/Data/EnemyList5.csv");
	}
	else//��O����
	{
		enemy->Init("./Assets/Data/EnemyList.csv");
	}
	//enemy->Init("./Assets/Data/EnemyList.csv");
	mActorManager->SetEnemyCount(enemy->GetEnemyCount());//�G�̐����Z�b�g
	delete(enemy);

	sound->Init();
	sound->Load("./Assets/Sound/a.mp3");//BGM
	sound->Load("./Assets/Sound/kettei.wav");
	input->Init();
	input->JoyInit();
	SceneManager::mCamera->Init(Vector2(0, 0));
	pose = false;
	SceneManager::mElapsedTime->Init();
	if (!mActorManager->GetPlayer())//�v���C���[�����Ȃ����
	{
		new Player(Vector2(50, 50));
	}
}

void GamePlay::Update()
{
	input->JoyUpdate();//�|�[�Y���ł��R���g���[���[���������悤��
	mInputTimers->Update();//����x���p	
	int Cr = GetColor(255, 255, 255);
	//DrawFormatString(500, 0, Cr, "%d:%0.2f", SceneManager::mElapsedTime->Now(), SceneManager::mElapsedTime->Rate() - int(SceneManager::mElapsedTime->Rate()));
	//DrawFormatString(500, 0, Cr, "%d", int(SceneManager::mElapsedTime->Now()));
	if (pose)//�|�[�Y��
	{
		
		DrawString(300, 100, "�|�[�Y��  �Q�[���p�b�h or �L�[�{�[�h", Cr);
		DrawString(300, 150, "�Q�[���ɖ߂�@START    or     P", Cr);
		DrawString(300, 200, "���Z�b�g�@�@�@ X       or     R", Cr);
		DrawString(300, 250, "�I���@�@�@�@�@BACK     or     B", Cr);
		if (mInputTimers->IsTime())
		{
			if (input->PadDown(JoyCode::Joy_Start) || input->GetKeyDown(P))
			{
				sound->PlaySE("./Assets/Sound/kettei.wav");
				pose = false;
				mInputTimers->SetTime(0.3f);
			}
			if (input->PadDown(JoyCode::Joy_X) || input->GetKeyDown(R))
			{
				sound->PlaySE("./Assets/Sound/kettei.wav");
				Reset();
			}
			if (input->PadDown(JoyCode::Joy_Back) || input->GetKeyDown(B))
			{
				sound->PlaySE("./Assets/Sound/kettei.wav");
				NextScene();
			}
		}
	}
	else//�|�[�Y�łȂ��Ȃ�
	{
		SceneManager::mElapsedTime->Update();//���Ԃ��X�V
		mActorManager->Update();
		mActorManager->Hit();
		if (mActorManager->GetPlayer())
		{
			SceneManager::mCamera->GetPPos(mActorManager->GetPlayer()->GetPosition());
			SceneManager::mCamera->Update();
			if (mStageName == "map")
			{
				SceneManager::mCamera->CameraPos.y -= 32;
			}
		}
		sound->PlayBGM("./Assets/Sound/a.mp3");
		if (input->GetKeyDown(B))
		{
			NextScene();
		}

		if (!mActorManager->GetPlayer())//�v���C���[������ł�����
		{
			//���Z�b�g
			Reset();
		}

		if (mActorManager->GetPlayer()->RGoal() || mActorManager->GetEnemyCount() == 0)//�S�[�������܂��͓G�����ׂē|����
		{
			NextScene();
		}

		if (mInputTimers->IsTime())
		{
			if (input->GetKeyDown(P) || input->PadDown(Joy_Start))
			{
				sound->PlaySE("./Assets/Sound/kettei.wav");
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
}

void GamePlay::NextScene()
{
	mSceneChanger->ChangeScene(SceneEnding);
}

void GamePlay::Reset()
{
	mActorManager->End();
	mActorManager->Clear();
	sound->StopBGM("./Assets/Sound/a.mp3");
	Init();
}
