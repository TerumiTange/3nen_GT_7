#include "Ending.h"
#include "SceneManager.h"

Ending::Ending(ISceneChanger * changer) :
	BaseScene(changer),
	input(new Input()),
	mNumber(new Renderer("Number")),
	sound(new Sound())
{
}

Ending::~Ending()
{
	delete(input);
	delete(mNumber);
}

void Ending::Init()
{
	input->Init();
	sound->Init();
	sound->Load("./Assets/Sound/kettei.wav");
}

void Ending::Update()
{
	input->JoyUpdate();
	if (input->GetKeyDown(B) || input->PadDown(Joy_B))
	{
		sound->PlaySE("./Assets/Sound/kettei.wav");
		NextScene();
	}
}

void Ending::Draw()
{
	int Cr = GetColor(255, 0, 0);
	SetFontSize(32);
	DrawString(380, 200, "ゲームクリア", Cr);
	DrawString(430, 250, "B PUSH", Cr);
	DrawString(380, 150, "ここにスコアが入る予定", Cr);
	mNumber->DrawNumber(Vector2(400, 50), SceneManager::mElapsedTime->Now());//かかった時間表示

}

void Ending::NextScene()
{
	mSceneChanger->ChangeScene(SceneTitle);
}
