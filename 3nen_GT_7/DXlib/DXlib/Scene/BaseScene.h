#pragma once
#include "ISceneChanger.h"

class BaseScene
{
protected:
	ISceneChanger* mSceneChanger;
public:
	BaseScene(ISceneChanger* changer);
	virtual ~BaseScene() {};
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};