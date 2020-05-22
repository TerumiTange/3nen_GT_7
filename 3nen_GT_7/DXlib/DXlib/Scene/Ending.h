#pragma once
#include "BaseScene.h"
#include "../System/Input.h"
#include "../Device/Renderer.h"
#include "../Device/Sound.h"
#include "../System/CountDownTimer.h"

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
	int s;//�Z���N�g
	int r;//���X�^�[�g
	int choice;//���ݑI��
	CountDownTimer* timer;//�x���p
};

enum EndMenu
{
	e_select,
	e_restart,

	endNum
};

