#include "SceneManager.h"
#include <memory>

SceneManager::SceneManager():
	mNextScene(SceneNone)
{
	mScene = (BaseScene*) new Title(this);
}

SceneManager::~SceneManager()
{
	delete(mScene);
	
}

void SceneManager::Init()
{
	mScene->Init();
}

void SceneManager::Update()
{
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
	}
	
	mScene->Update();
}

void SceneManager::Draw()
{
	mScene->Draw();
}

void SceneManager::ChangeScene(SceneType nextScene)
{
	mNextScene = nextScene;
}
