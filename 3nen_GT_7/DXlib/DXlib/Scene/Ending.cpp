#include "Ending.h"
#include "SceneManager.h"
#include <iostream>
#include <fstream>

Ending::Ending(ISceneChanger * changer) :
	BaseScene(changer),
	input(new Input()),
	mNumber(new Renderer("Number")),
	//sound(new Sound()),
	timer(new CountDownTimer()),
	NewScore(false)
{
	s = 350;
	r = 400;
	choice = e_select;
	clear = SceneManager::gameClear;
}

Ending::~Ending()
{
	//sound->StopBGM("./Assets/Sound/Result.mp3");
	//sound->StopBGM("./Assets/Sound/GameOver.mp3");
	SceneManager::sound->StopBGM("./Assets/Sound/Result.mp3");
	SceneManager::sound->StopBGM("./Assets/Sound/GameOver.mp3");
	delete(input);
	delete(mNumber);
	delete(timer);
	//delete(sound);
}

void Ending::Init()
{
	numScore = 0;
	timeScore = 0;
	input->Init();
	//sound->Init();
	//sound->Load("./Assets/Sound/kettei.wav");
	//sound->Load("./Assets/Sound/migration.wav");
	//sound->Load("./Assets/Sound/Result.mp3");//クリア
	//sound->Load("./Assets/Sound/GameOver.mp3");//ゲームオーバー
	if (clear)//ゲームをクリアしていたら
	{
		//ここにタイムによる加点処理
		float time = SceneManager::mElapsedTime->Now();
		timeScore += (time < 60) ? 500 : 0;
		timeScore += (time < 70) ? 400 : 0;
		timeScore += (time < 80) ? 300 : 0;
		timeScore += (time < 90) ? 200 : 0;
		timeScore += (time < 100) ? 100 : 0;


		numScore = timeScore + SceneManager::score;
		std::string stage;
		stage = SceneManager::stageName;
		if (stage == "stage1")//書き込む
		{
			NewScore = SceneManager::mScore->Write("./Assets/Data/Score1.txt", numScore);
		}
		else if (stage == "stage2")
		{
			NewScore = SceneManager::mScore->Write("./Assets/Data/Score2.txt", numScore);
		}
		else if (stage == "stage3")
		{
			NewScore = SceneManager::mScore->Write("./Assets/Data/Score3.txt", numScore);
		}
		else if (stage == "stage4")
		{
			NewScore = SceneManager::mScore->Write("./Assets/Data/Score4.txt", numScore);
		}
		else if (stage == "stage5")
		{
			NewScore = SceneManager::mScore->Write("./Assets/Data/Score5.txt", numScore);
		}
	}
}

void Ending::Update()
{
	if (clear)
	{
		//sound->PlayBGM("./Assets/Sound/Result.mp3");
		SceneManager::sound->PlayBGM("./Assets/Sound/Result.mp3");
	}
	else
	{
		//sound->PlayBGM("./Assets/Sound/GameOver.mp3");
		SceneManager::sound->PlayBGM("./Assets/Sound/GameOver.mp3");
	}

	input->JoyUpdate();
	timer->Update();
	if (input->GetKeyDown(B) || input->PadDown(Joy_B))
	{
		//sound->PlaySE("./Assets/Sound/kettei.wav");
		SceneManager::sound->PlaySE("./Assets/Sound/kettei.wav");
		NextScene();
	}
	if (!timer->IsTime())return;

	if (input->GetKeyDown(S) || input->GetKeyDown(DOWNARROW) || input->PadDown(JoyCode::Joy_Down))//下
	{
		//sound->PlaySE("./Assets/Sound/migration.wav");
		SceneManager::sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + 1) % endNum;//1つ下げる
		timer->SetTime(0.3f);
		return;
	}
	if (input->GetKeyDown(W) || input->GetKeyDown(UPARROW) || input->PadDown(JoyCode::Joy_Up))
	{
		//sound->PlaySE("./Assets/Sound/migration.wav");
		SceneManager::sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + (endNum - 1)) % endNum;//1つ上げる
		timer->SetTime(0.3f);
		return;
	}

	if (input->Vertical() > 0)
	{
		//sound->PlaySE("./Assets/Sound/migration.wav");
		SceneManager::sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + 1) % endNum;//1つ下げる
		timer->SetTime(0.3f);
		return;
	}
	if (input->Vertical() < 0)
	{
		//sound->PlaySE("./Assets/Sound/migration.wav");
		SceneManager::sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + (endNum - 1)) % endNum;//1つ上げる
		timer->SetTime(0.3f);
		return;
	}

}

void Ending::Draw()
{
	int Cr = GetColor(255, 0, 0);
	SetFontSize(32);
	if (clear)
	{
		int figure;//タイムの秒数(整数)
		figure = SceneManager::mElapsedTime->Now();
		for (auto count = 1;; ++count)
		{
			if (figure < 10)
			{
				figure = count;//桁数になる
				//continue;
				break;
			}
			figure /= 10;
		}
		DrawString(380, 50, "ゲームクリア", Cr);
		DrawFormatString(380, 100, Cr, "スコア：%d", SceneManager::score);//ゲームによるスコア表示
		DrawString(380, 150, "タイムスコア", Cr);
		mNumber->DrawNumber(Vector2(396 - (32 * figure), 200) , SceneManager::mElapsedTime->Now());//かかった時間表示
		DrawFormatString(500, 200, Cr, " : %d", timeScore);//タイムによるスコア表示
		DrawFormatString(380, 250, Cr, "トータルスコア：%d", numScore);//合計スコア表示
		if (NewScore)
		{
			DrawString(380, 300, "ハイスコア更新！！", Cr);
		}
	}
	else
	{
		DrawString(380, 50, "ゲームオーバー", Cr);
	}
	
	
	DrawString(380, s, "ゲームセレクトへ", Cr);
	DrawString(380, r, "もう一度同じステージで遊ぶ", Cr);
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
