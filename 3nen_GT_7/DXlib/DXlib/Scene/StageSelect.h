#pragma once
#include "../Device/Dx.h"
#include"BaseScene.h"

#include "../Device/Sound.h"
#include "../System/Input.h"
#include "../Device/Camera2d.h"
#include "../System/CountDownTimer.h"
#include "../Utility/Vector2.h"
#include "SceneManager.h"
#include "../Device/Sound.h"
#include "../Device/Renderer.h"

class StageSelect :public BaseScene
{
public:
	StageSelect(ISceneChanger* changer);
	~StageSelect();
	void CSVReader();
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
	//Sound* sound;
	Renderer* mRenderer;
	Renderer* mBack;
	Renderer* mSelect;
	Renderer* mStage1;
	Renderer* mStage2;
	Renderer* mStage3;
	Renderer* mStage4;
	Renderer* mStage5;
	Renderer* title;

	int Score1;
	int Score2;
	int Score3;
	int Score4;
	int Score5;
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