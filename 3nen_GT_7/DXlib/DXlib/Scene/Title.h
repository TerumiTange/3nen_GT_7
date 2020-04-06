#pragma once
#include "BaseScene.h"
#include "../System/Input.h"

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
};