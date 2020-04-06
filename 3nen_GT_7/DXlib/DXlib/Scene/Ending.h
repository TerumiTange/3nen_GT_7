#pragma once
#include "BaseScene.h"
#include "../System/Input.h"

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
};

