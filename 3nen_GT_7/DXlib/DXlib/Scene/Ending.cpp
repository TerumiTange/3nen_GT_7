#include "Ending.h"
#include "SceneManager.h"

Ending::Ending(ISceneChanger * changer) :
	BaseScene(changer),
	input(new Input()),
	mNumber(new Renderer("Number")),
	sound(new Sound()),
	timer(new CountDownTimer())
{
	s = 300;
	r = 350;
	choice = e_select;
}

Ending::~Ending()
{
	delete(input);
	delete(mNumber);
	delete(timer);
}

void Ending::Init()
{
	input->Init();
	sound->Init();
	sound->Load("./Assets/Sound/kettei.wav");
	sound->Load("./Assets/Sound/migration.wav");
	//sound->Load("");BGM
}

void Ending::Update()
{
	
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
		choice = (choice + 1) % endNum;//1つ下げる
		timer->SetTime(0.3f);
		return;
	}
	if (input->GetKeyDown(W) || input->GetKeyDown(UPARROW) || input->PadDown(JoyCode::Joy_Up))
	{
		sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + (endNum - 1)) % endNum;//1つ上げる
		timer->SetTime(0.3f);
		return;
	}

	if (input->Vertical() > 0)
	{
		sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + 1) % endNum;//1つ下げる
		timer->SetTime(0.3f);
		return;
	}
	if (input->Vertical() < 0)
	{
		sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + (endNum - 1)) % endNum;//1つ上げる
		timer->SetTime(0.3f);
		return;
	}

}

void Ending::Draw()
{
	int Cr = GetColor(255, 0, 0);
	SetFontSize(32);
	if (SceneManager::gameClear)
	{
		DrawString(380, 50, "ゲームクリア", Cr);
		mNumber->DrawNumber(Vector2(400, 100), SceneManager::mElapsedTime->Now());//かかった時間表示
		DrawString(380, 150, "ここにスコアが入る予定", Cr);
		DrawString(380, 200, "ここに合計スコアが入る予定", Cr);
	}
	else
	{
		DrawString(380, 50, "ゲームオーバー", Cr);
	}
	
	
	DrawString(380, s, "ゲームセレクトへ", Cr);
	DrawString(380, r, "もう一度同じステージで遊ぶ", Cr);
	DrawString(0, 0, "B PUSH", Cr);
	int y;
	switch (choice)
	{
	case e_select:
		y = s;
		break;
	case e_restart:
		y = r;
		break;
	}
	DrawString(300, y, "■", GetColor(0, 255, 0));
}

void Ending::NextScene()
{
	switch (choice)
	{
	case e_select:
		mSceneChanger->ChangeScene(SceneSelect);
		break;
	case e_restart:
		mSceneChanger->ChangeScene(SceneGamePlay);
		break;
	default:
		mSceneChanger->ChangeScene(SceneTitle);
		break;
	}
}
