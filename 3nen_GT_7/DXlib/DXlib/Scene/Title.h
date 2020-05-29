#pragma once
#include "BaseScene.h"
#include "../System/Input.h"
#include "../System/CountDownTimer.h"
#include "../Device/Sound.h"
#include "../Device/Renderer.h"

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
	int choice;//現在選択中
	CountDownTimer* timer;//入力遅延をわざと起こすよう
	//Sound* sound;
	bool option;
	Renderer* mGra;//周りの画像
	Renderer* mBackGra;//背景
	Renderer* mTitleGra;//タイトルの画像
	int mBY;
};

enum eMenu
{
	start,  //ゲームスタート
	credit, //クレジット
	eMenuNum//本項目の数
};