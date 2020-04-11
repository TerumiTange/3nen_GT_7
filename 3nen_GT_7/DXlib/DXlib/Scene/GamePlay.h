#pragma once
#include "../Device/Dx.h"
#include"BaseScene.h"

#include "../Actor/Player.h"
#include "../Map/Map.h"
#include "../Device/Sound.h"
#include "../System/Input.h"
#include "Load.h"

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
	Player player;
	Map map;
	Sound sound;
	Input* input;
	Load* load;
};