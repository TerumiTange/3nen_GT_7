#include "Title.h"
#include "DxLib.h"
#include "SceneManager.h"

Title::Title(ISceneChanger* changer)
	:BaseScene(changer),
	input(new Input()),
	startY(130),
	creditY(210),
	timer(new CountDownTimer()),
	mGra(new Renderer("Wall2")),
	mBackGra(new Renderer(""))
	//sound(new Sound())
{
	choice = start;//最初はゲームスタートを選択
}

Title::~Title()
{
	SceneManager::sound->StopBGM("./Assets/Sound/Title.mp3");
	//sound->StopBGM("./Assets/Sound/Title.mp3");
	delete(input);
	delete(timer);
	delete(mGra);
	delete(mBackGra);
	//delete(sound);
}

void Title::Init()
{
	input->Init();
	//sound->Init();
	//sound->Load("./Assets/Sound/kettei.wav");//決定
	//sound->Load("./Assets/Sound/migration.wav");//カーソル
	//sound->Load("./Assets/Sound/Title.mp3");//BGM
	option = false;
}

void Title::Update()
{
	//sound->PlayBGM("./Assets/Sound/Title.mp3");//BGM
	SceneManager::sound->PlayBGM("./Assets/Sound/Title.mp3");
	printfDx("ゲームパッド数%d", GetJoypadNum());
	GetJoypadInputState(DX_INPUT_PAD1);
	input->JoyUpdate();
	timer->Update();

	if (!timer->IsTime())return;
	if (input->GetKeyDown(B) || input->PadDown(Joy_B))
	{
		//sound->PlaySE("./Assets/Sound/kettei.wav");
		SceneManager::sound->PlaySE("./Assets/Sound/kettei.wav");
		NextScene();
		timer->SetTime(0.3f);
		return;
	}

	if (option)return;
	if (input->GetKeyDown(S) || input->GetKeyDown(DOWNARROW) || input->PadDown(JoyCode::Joy_Down))//下
	{
		//sound->PlaySE("./Assets/Sound/migration.wav");
		SceneManager::sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + 1) % eMenuNum;//1つ下げる
		timer->SetTime(0.3f);
		return;
	}
	if (input->GetKeyDown(W) || input->GetKeyDown(UPARROW) || input->PadDown(JoyCode::Joy_Up))
	{
		//sound->PlaySE("./Assets/Sound/migration.wav");
		SceneManager::sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + (eMenuNum - 1)) % eMenuNum;//1つ上げる
		timer->SetTime(0.3f);
		return;
	}

	if (input->Vertical() > 0)
	{
		//sound->PlaySE("./Assets/Sound/migration.wav");
		SceneManager::sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + 1) % eMenuNum;//1つ下げる
		timer->SetTime(0.3f);
		return;
	}
	if (input->Vertical() < 0)
	{
		//sound->PlaySE("./Assets/Sound/migration.wav");
		SceneManager::sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + (eMenuNum - 1)) % eMenuNum;//1つ上げる
		timer->SetTime(0.3f);
		return;
	}
}

void Title::Draw()
{
	mBackGra->Drawb(0, 0);//背景描画
	for (int i = 0; i < 1024; i += 32)
	{
		mGra->Drawb(i, 0);
		mGra->Drawb(i, 544);
	}
	for (int i = 32; i < 544 ; i += 32)
	{
		mGra->Drawb(0, i);
		mGra->Drawb(992, i);
	}

	int Cr = GetColor(255, 0, 0);
	SetFontSize(32);
	if (option)
	{
		DrawString(150, 150, "Lスティック   :   左右移動", Cr);
		DrawString(150, 200, "Aボタン       :   入力方向に高速移動", Cr);
		DrawString(150, 250, "STARTボタン   :   ポーズ", Cr);
		DrawString(150, 300, "Bボタン       :   決定", Cr);
	}
	else
	{
		DrawString(150, 50, "Title B PUSH", Cr);
		DrawString(150, startY, "スタート", Cr);//130
		DrawString(150, creditY, "操作説明", Cr);//210
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
		option = (option) ? false : true;
		//mSceneChanger->ChangeScene(SceneCredit);
		//mSceneChanger->ChangeScene(SceneSelect);
		break;
	default:
	  mSceneChanger->ChangeScene(SceneSelect);//例外が発生したら
		break;
	}
	//mSceneChanger->ChangeScene(SceneGamePlay);
}
