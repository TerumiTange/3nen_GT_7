#pragma once
#include "../Device/Dx.h"

#include "BaseScene.h"
#include "Title.h"
#include "StageSelect.h"
#include "GamePlay.h"
#include "Ending.h"

#include "../Device/Fader.h"

#include "../System/CountUpTimer.h"
#include "../Device/Camera2d.h"
#include "../Device/Sound.h"

#include "Score.h"

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
	static CountUpTimer* mElapsedTime;//�X�e�[�W��̌o�ߎ���
	static Camera2d* mCamera;
	static bool gameClear;//�Q�[�����N���A�������ǂ���
	static Score* mScore;
	static int score;//�X�R�A
	static Sound* sound;
	
private:
	BaseScene* mScene;
	SceneType mNextScene;
	Fader* mfader;//�t�F�[�h
};
