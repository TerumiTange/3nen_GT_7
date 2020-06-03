#include "SceneManager.h"
#include "../Actor/Actor.h"
#include <memory>

SceneManager::SceneManager():
	mNextScene(SceneNone),
	mfader(new Fader())
{
	mScene = (BaseScene*) new Title(this);
	//mScene = (BaseScene*) new Ending(this);
	sound->Load("./Assets/Sound/kettei.wav");//決定
	sound->Load("./Assets/Sound/migration.wav");//カーソル
	sound->Load("./Assets/Sound/Title.mp3");//BGM
	sound->Load("./Assets/Sound/GamePlay.mp3");//BGM
	sound->Load("./Assets/Sound/Result.mp3");//クリア
	sound->Load("./Assets/Sound/GameOver.mp3");//ゲームオーバー
}

SceneManager::~SceneManager()
{
	delete(mScene);
	delete(mfader);
	delete(mElapsedTime);
	delete(Actor::mElectricTimer);//最後にメモリを解放するため
	delete(mCamera);
	delete(mScore);
	delete(sound);
}

void SceneManager::Init()
{
	mScene->Init();
}

void SceneManager::Update()
{
	mfader->Update();
	if (mfader->GetNowFader())return;
	if (mNextScene != SceneNone)
	{
		delete mScene;
		switch (mNextScene)
		{
		case SceneTitle:
			mScene = (BaseScene*)new Title(this);
			break;
		case SceneSelect:
			mScene = (BaseScene*)new StageSelect(this);
			break;
		case SceneGamePlay:
			mScene = (BaseScene*) new GamePlay(this,stageName);
			break;
		case SceneEnding:
			mScene = (BaseScene*)new Ending(this);
		default:
			break;
		}
		mNextScene = SceneNone;
		mScene->Init();
		mfader->SetFadeIn(1);
		mfader->SwitchFade(false);
	}
	if (mfader->GetNowFader())return;
	mScene->Update();
}

void SceneManager::Draw()
{
	mScene->Draw();
	mfader->Draw();
}

void SceneManager::ChangeScene(SceneType nextScene)
{
	mfader->SetFadeOut(1);
	mfader->SwitchFade(true);
	mNextScene = nextScene;
}

const char* SceneManager::stageName = "";
CountUpTimer* SceneManager::mElapsedTime = new CountUpTimer();
Camera2d* SceneManager::mCamera = new Camera2d();
bool SceneManager::gameClear = false;
Score* SceneManager::mScore = new Score();
int SceneManager::score = 0;
Sound* SceneManager::sound = new Sound();