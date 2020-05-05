#pragma once
#include "../Device/Dx.h"
#include"BaseScene.h"

#include "../Device/Sound.h"
#include "../System/Input.h"
#include "../Device/Camera2d.h"

class ActorManager;
class Camera;

class GamePlay : public BaseScene
{
public:
	GamePlay(ISceneChanger* changer);
	~GamePlay();
	void Init() override;
	void Update() override;
	void Draw() override;
	void NextScene();

private:
	ActorManager* mActorManager;
	Sound sound;
	Input* input;
	Camera2d* camera;
};