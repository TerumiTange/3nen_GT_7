#include "SceneManager.h"
#include <memory>

SceneManager::SceneManager():
	mNextScene(SceneNone),
	mfader(new Fader())
{
	mScene = (BaseScene*) new Title(this);
}

SceneManager::~SceneManager()
{
	delete(mScene);
	delete(mfader);
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
		case SceneGamePlay:
			mScene = (BaseScene*) new GamePlay(this);
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
