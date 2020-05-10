#pragma once
#include "../Device/Dx.h"

#include "BaseScene.h"
#include "Title.h"
#include "StageSelect.h"
#include "GamePlay.h"
#include "Ending.h"

#include "../Device/Fader.h"

#include "../System/CountUpTimer.h"

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

	static const char* stageName;
	static CountUpTimer* mElapsedTime;//ステージ上の経過時間
	
private:
	BaseScene* mScene;
	SceneType mNextScene;
	Fader* mfader;//フェード
};
