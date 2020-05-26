#include "Ending.h"
#include "SceneManager.h"
#include <iostream>
#include <fstream>

Ending::Ending(ISceneChanger * changer) :
	BaseScene(changer),
	input(new Input()),
	mNumber(new Renderer("Number")),
	sound(new Sound()),
	timer(new CountDownTimer()),
	NewScore(false)
{
	s = 300;
	r = 350;
	choice = e_select;
}

Ending::~Ending()
{
	sound->StopBGM("./Assets/Sound/Result.mp3");
	sound->StopBGM("./Assets/Sound/GameOver.mp3");
	delete(input);
	delete(mNumber);
	delete(timer);
	delete(sound);
}

void Ending::Init()
{
	numScore = 0;
	timeScore = 0;
	input->Init();
	sound->Init();
	sound->Load("./Assets/Sound/kettei.wav");
	sound->Load("./Assets/Sound/migration.wav");
	sound->Load("./Assets/Sound/Result.mp3");//クリア
	sound->Load("./Assets/Sound/GameOver.mp3");//ゲームオーバー
	if (SceneManager::gameClear)//ゲームをクリアしていたら
	{
		//ここにタイムによる加点処理
		//timeScore;
		//
		numScore = timeScore + SceneManager::score;
		std::string stage;
		stage = SceneManager::stageName;
		if (stage == "stage1")//書き込む
		{
			NewScore = SceneManager::mScore->Write("./Assets/Data/Score1.txt", numScore);
		}
		else if (stage == "stage2")
		{
			NewScore = SceneManager::mScore->Write("./Assets/Data/Score1.txt", numScore);
		}
		else if (stage == "stage3")
		{
			NewScore = SceneManager::mScore->Write("./Assets/Data/Score1.txt", numScore);
		}
		else if (stage == "stage4")
		{
			NewScore = SceneManager::mScore->Write("./Assets/Data/Score1.txt", numScore);
		}
		else if (stage == "stage5")
		{
			NewScore = SceneManager::mScore->Write("./Assets/Data/Score1.txt", numScore);
		}
	}
}

void Ending::Update()
{
	if (SceneManager::gameClear)
	{
		sound->PlayBGM("./Assets/Sound/Result.mp3");
	}
	else
	{
		sound->PlayBGM("./Assets/Sound/GameOver.mp3");
	}

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
		DrawFormatString(380, 100, Cr, "スコア：%d", SceneManager::score);//ゲームによるスコア表示
		mNumber->DrawNumber(Vector2(300, 150), SceneManager::mElapsedTime->Now());//かかった時間表示
		DrawFormatString(500, 150, Cr, " : %d", timeScore);//タイムによるスコア表示
		DrawFormatString(380, 200, Cr, "トータルスコア：%d", numScore);//合計スコア表示
		if (NewScore)
		{
			DrawString(380, 250, "ニュースコア！！", Cr);
		}
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
