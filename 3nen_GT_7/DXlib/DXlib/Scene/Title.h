#pragma once
#include "BaseScene.h"
#include "../System/Input.h"
#include "../System/CountDownTimer.h"

class Title :public BaseScene
{
public:
	Title(ISceneChanger* changer);
	~Title();
	void Init() override;
	void Update() override;
	void Draw() override;
	void NextScene();
private:
	Input* input;
	int startY;//ゲームスタート
	int creditY;//クレジット
	int configFllY;//フルスク
	int configModeY;//ウィンドウ
	int choice;//現在選択中
	CountDownTimer* timer;//入力遅延をわざと起こすよう
};

enum eMenu
{
	start,  //ゲームスタート
	credit, //クレジット
	full,  //フルスク
	mode,  //ウィンドウ
	eMenuNum//本項目の数
};