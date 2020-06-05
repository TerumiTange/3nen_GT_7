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
	Renderer* mBigNumber;
	Sound* sound;
	Renderer* mGra;
	int choice;//���ݑI��
	CountDownTimer* timer;//�x���p
	bool NewScore;
	int timeScore;//�^�C���ɂ��X�R�A
	int numScore;//���v�X�R�A
	bool clear;
	std::string stage;

	Renderer* mGOverGra;
	Renderer* mChoiceGra;
	Renderer* mClear1;
	Renderer* mClear2;
	bool mC;//��ʂ�2���ǂ���
	Renderer* HiGra;
};

enum EndMenu
{
	e_select,
	e_restart,

	endNum
};

