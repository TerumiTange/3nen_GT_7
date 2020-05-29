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
	//Sound* sound;
	int s;//セレクト
	int r;//リスタート
	int n;//次のステージへ
	int choice;//現在選択中
	CountDownTimer* timer;//遅延用
	bool NewScore;
	int timeScore;//タイムによるスコア
	int numScore;//合計スコア
	bool clear;
	std::string stage;
};

enum EndMenu
{
	e_select,
	e_restart,
	e_nextstage,

	endNum
};

