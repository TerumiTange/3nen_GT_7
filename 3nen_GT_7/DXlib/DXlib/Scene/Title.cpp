#include "Title.h"
#include "DxLib.h"

Title::Title(ISceneChanger* changer)
	:BaseScene(changer),
	input(new Input()),
	startY(100),
	creditY(150),
	timer(new CountDownTimer()),
	sound(new Sound())
{
	choice = start;//最初はゲームスタートを選択
}

Title::~Title()
{
	//sound->StopBGM("");
	delete(input);
	delete(timer);
	delete(sound);
}

void Title::Init()
{
	input->Init();
	sound->Init();
	sound->Load("./Assets/Sound/kettei.wav");//決定
	sound->Load("./Assets/Sound/migration.wav");//カーソル
	//sound->Load("");//BGM
}

void Title::Update()
{
	//sound->PlayBGM("");//BGM
	printfDx("ゲームパッド数%d", GetJoypadNum());
	GetJoypadInputState(DX_INPUT_PAD1);
	input->JoyUpdate();
	timer->Update();


	if (input->GetKeyDown(B) || input->PadDown(Joy_B))
	{
		sound->PlaySE("./Assets/Sound/kettei.wav");
		NextScene();
	}
	if (!timer->IsTime())return;
	if (input->GetKeyDown(S) || input->GetKeyDown(DOWNARROW) || input->PadDown(JoyCode::Joy_Down))//下
	{
		sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + 1) % eMenuNum;//1つ下げる
		timer->SetTime(0.3f);
		return;
	}
	if (input->GetKeyDown(W) || input->GetKeyDown(UPARROW) || input->PadDown(JoyCode::Joy_Up))
	{
		sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + (eMenuNum - 1)) % eMenuNum;//1つ上げる
		timer->SetTime(0.3f);
		return;
	}

	if (input->Vertical() > 0)
	{
		sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + 1) % eMenuNum;//1つ下げる
		timer->SetTime(0.3f);
		return;
	}
	if (input->Vertical() < 0)
	{
		sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + (eMenuNum - 1)) % eMenuNum;//1つ上げる
		timer->SetTime(0.3f);
		return;
	}
}

void Title::Draw()
{
	int Cr = GetColor(255, 0, 0);
	SetFontSize(16);
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
		break;
	}
	DrawString(100, y, "■", GetColor(0, 255, 0));
}

void Title::NextScene()
{
	switch (choice)
	{
	case start:
		//mSceneChanger->ChangeScene(SceneSelect);
		mSceneChanger->ChangeScene(SceneSelect);
		break;
	case credit:
		//mSceneChanger->ChangeScene(SceneCredit);
		mSceneChanger->ChangeScene(SceneSelect);
		break;
	default:
	  mSceneChanger->ChangeScene(SceneSelect);//例外が発生したら
		break;
	}
	//mSceneChanger->ChangeScene(SceneGamePlay);
}
