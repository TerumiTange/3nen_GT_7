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
	const char* mStageName;//�X�e�[�W�̖��O
	bool pose;//�|�[�Y�p
	CountDownTimer* mInputTimers;//�o�߂�������
	Renderer* mRenderer;//�`��p
	Physics* mPhysics;
};