#pragma once
#include "BaseScene.h"
#include "../System/Input.h"
#include "../System/CountDownTimer.h"

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
	int startY;//�Q�[���X�^�[�g
	int creditY;//�N���W�b�g
	int choice;//���ݑI��
	CountDownTimer* timer;//���͒x�����킴�ƋN�����悤
};

enum eMenu
{
	start,  //�Q�[���X�^�[�g
	credit, //�N���W�b�g

	eMenuNum//�{���ڂ̐�
};