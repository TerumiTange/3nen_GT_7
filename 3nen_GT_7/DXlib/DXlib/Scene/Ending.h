#pragma once
#include "BaseScene.h"
#include "../System/Input.h"
#include "../Device/Renderer.h"
#include "../Device/Sound.h"
#include "../System/CountDownTimer.h"

class Ending :public BaseScene
{
public:
	Ending(ISceneChanger* changer);
	~Ending();
	void Init() override;
	void Update() override;
	void Draw() override;
	void NextScene();

private:
	Input* input;
	Renderer* mNumber;
	Renderer* mBigNumber;
	Sound* sound;
	Renderer* mGra;
	int choice;//現在選択中
	CountDownTimer* timer;//遅延用
	bool NewScore;
	int timeScore;//タイムによるスコア
	int numScore;//合計スコア
	bool clear;
	std::string stage;

	Renderer* mGOverGra;
	Renderer* mChoiceGra;
	Renderer* mClear1;
	Renderer* mClear2;
	bool mC;//画面が2かどうか
	Renderer* HiGra;
};

enum EndMenu
{
	e_select,
	e_restart,

	endNum
};

