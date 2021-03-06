#pragma once
#include "../Device/Dx.h"
#include"BaseScene.h"

#include "../Device/Sound.h"
#include "../System/Input.h"
#include "../Device/Camera2d.h"
#include "../System/CountDownTimer.h"
#include "../Device/Renderer.h"

class ActorManager;
class Camera;
class Physics;

class GamePlay : public BaseScene
{
public:
	GamePlay(ISceneChanger* changer,const char* name);
	~GamePlay();
	void Init() override;
	void Update() override;
	void Draw() override;
	void NextScene();
	void Reset();

private:
	ActorManager* mActorManager;
	Sound* sound;
	Input* input;
	const char* mStageName;//ステージの名前
	bool pose;//ポーズ用
	CountDownTimer* mInputTimers;//経過した時間
	Renderer* mRenderer;//描画用
	Renderer* mBackGround;//背景画
	Renderer* mExplain1;//操作説明1
	Renderer* mExplain2;//操作説明2
	Renderer* mExplain3;//操作説明3
	Physics* mPhysics;
	Renderer* mPause;
};