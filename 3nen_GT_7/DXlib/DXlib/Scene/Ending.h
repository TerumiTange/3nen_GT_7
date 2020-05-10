#pragma once
#include "BaseScene.h"
#include "../System/Input.h"
#include "../Device/Renderer.h"
#include "../Device/Sound.h"

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
	Sound* sound;
};

