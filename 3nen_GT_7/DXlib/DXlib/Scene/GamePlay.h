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
	Physics* mPhysics;
};