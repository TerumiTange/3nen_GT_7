#include "Title.h"
#include "DxLib.h"

Title::Title(ISceneChanger* changer)
	:BaseScene(changer),
	input(new Input())
{
}

Title::~Title()
{
	delete(input);
}

void Title::Init()
{
	input->Init();
}

void Title::Update()
{
	input->JoyUpdate();
	if (input->GetKeyDown(A) || input->PadDown(Joy_A))
	{
		NextScene();
	}
}

void Title::Draw()
{
	int Cr = GetColor(255, 0, 0);
	DrawString(50, 50, "Title A PUSH", Cr);
}

void Title::NextScene()
{
	mSceneChanger->ChangeScene(SceneGamePlay);
}
