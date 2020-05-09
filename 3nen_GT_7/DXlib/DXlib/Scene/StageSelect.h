#pragma once
#include "../Device/Dx.h"
#include"BaseScene.h"

#include "../Device/Sound.h"
#include "../System/Input.h"
#include "../Device/Camera2d.h"
#include "../System/CountDownTimer.h"
#include "../Utility/Vector2.h"
#include "SceneManager.h"

class StageSelect :public BaseScene
{
public:
	StageSelect(ISceneChanger* changer);
	~StageSelect();
	void Init()override;
	void Update()override;
	void Draw()override;
	void NextScene();

private:
	Input* mInput;
	CountDownTimer* mTimers;//“ü—Í’x‰„‚ğ‹N‚±‚·‚æ‚¤
	Vector2* stage1Pos;
	Vector2* stage2Pos;
	Vector2* stage3Pos;
	Vector2* stage4Pos;
	Vector2* stage5Pos;
	Vector2* stage6Pos;
	int choice;//Œ»İ‘I‘ğ’†
};

enum eStage
{
	stage1,
	stage2,
	stage3,
	stage4,
	stage5,
	stage6,

	eStageNum//–{€–Ú‚Ì”
};