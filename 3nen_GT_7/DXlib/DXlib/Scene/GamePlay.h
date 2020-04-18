#pragma once
#include "../Device/Dx.h"
#include"BaseScene.h"

#include "../Device/Sound.h"
#include "../System/Input.h"

class ActorManager;


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
};