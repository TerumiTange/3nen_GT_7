#include "Title.h"
#include "DxLib.h"

Title::Title(ISceneChanger* changer)
	:BaseScene(changer),
	input(new Input()),
	startY(100),
	creditY(150),
	timer(new CountDownTimer())
{
	choice = start;//最初はゲームスタートを選択
}

Title::~Title()
{
	delete(input);
	delete(timer);
}

void Title::Init()
{
	input->Init();
}

void Title::Update()
{
	input->JoyUpdate();
	timer->Update();

	if (input->GetKeyDown(B) || input->PadDown(Joy_B))
	{
		NextScene();
	}
	if (!timer->IsTime())return;
	if (input->GetKeyDown(S) || input->GetKeyDown(DOWNARROW) || input->PadDown(JoyCode::Joy_Down) || (input->Vertical() < 0))//下
	{
		choice = (choice + 1) % eMenuNum;//1つ下げる
		timer->SetTime(0.2f);
	}
	if (input->GetKeyDown(W) || input->GetKeyDown(UPARROW) || input->PadDown(JoyCode::Joy_Up) || (input->Vertical() > 0))
	{
		choice = (choice + (eMenuNum - 1)) % eMenuNum;//1つ上げる
		timer->SetTime(0.2f);
	}
}

void Title::Draw()
{
	int Cr = GetColor(255, 0, 0);
	DrawString(150, 50, "Title B PUSH　どっち選んでもゲームプレイに行くけどね", Cr);
	DrawString(150, startY, "スタート", Cr);
	DrawString(150, creditY, "クレジット", Cr);
	int y;
	switch (choice)
	{
	case start:
		y = startY;
		break;
	case credit:
		y = creditY;
		break;
	}
	DrawString(100, y, "■", GetColor(0, 255, 0));
}

void Title::NextScene()
{
	//switch (choice)
	//{
	//case start:
	//	mSceneChanger->ChangeScene(SceneSelect);
	//	break;
	//case credit:
	//	mSceneChanger->ChangeScene(SceneCredit);
	//default:
	//  mSceneChanger->ChangeScene(SceneSelect);//例外が発生したら
	//	break;
	//}
	mSceneChanger->ChangeScene(SceneGamePlay);
}
