#include "Ending.h"

Ending::Ending(ISceneChanger * changer) :
	BaseScene(changer),
	input(new Input())
{
}

Ending::~Ending()
{
	delete(input);
}

void Ending::Init()
{
	input->Init();
}

void Ending::Update()
{
	input->JoyUpdate();
	if (input->GetKeyDown(Y) || input->PadDown(Joy_Y))
	{
		NextScene();
	}
}

void Ending::Draw()
{
	int Cr = GetColor(255, 0, 0);
	SetFontSize(16);
	DrawString(50, 50, "Ending  Y PUSH", Cr);
}

void Ending::NextScene()
{
	mSceneChanger->ChangeScene(SceneTitle);
}
