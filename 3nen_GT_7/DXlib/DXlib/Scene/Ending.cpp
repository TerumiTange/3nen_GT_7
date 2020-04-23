#include "Ending.h"

Ending::Ending(ISceneChanger * changer) :
	BaseScene(changer),
	input(new Input())
{
}

Ending::~Ending()
{
}

void Ending::Init()
{
	input->Init();
}

void Ending::Update()
{
	if (input->GetKeyDown(A))
	{
		NextScene();
	}
}

void Ending::Draw()
{
	int Cr = GetColor(255, 0, 0);
	DrawString(50, 50, "Ending  A PUSH", Cr);
}

void Ending::NextScene()
{
	mSceneChanger->ChangeScene(SceneTitle);
}
