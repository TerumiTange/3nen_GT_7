#pragma once
#include "../Device/Dx.h"

#include "BaseScene.h"
#include "Title.h"
#include "GamePlay.h"
#include "Ending.h"

#include "../Device/Fader.h"

class SceneManager:
	public ISceneChanger
{
public:
	SceneManager();
	~SceneManager();
	void Init();
	void Update();
	void Draw();
	void ChangeScene(SceneType nextScene)override;

private:
	BaseScene* mScene;
	SceneType mNextScene;
	Fader* mfader;//フェード
};
