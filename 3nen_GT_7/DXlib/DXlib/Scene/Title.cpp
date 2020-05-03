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
	if (input->GetKeyDown(B) || input->PadDown(Joy_B))
	{
		NextScene();
	}
}

void Title::Draw()
{
	int Cr = GetColor(255, 0, 0);
	DrawString(50, 50, "Title B PUSH", Cr);
}

void Title::NextScene()
{
	mSceneChanger->ChangeScene(SceneGamePlay);
}
