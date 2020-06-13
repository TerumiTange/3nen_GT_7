#include "Ending.h"
#include "SceneManager.h"
#include <iostream>
#include <fstream>

Ending::Ending(ISceneChanger * changer) :
	BaseScene(changer),
	input(new Input()),
	mNumber(new Renderer("Number")),
	mBigNumber(new Renderer("BigNumber")),
	sound(new Sound()),
	timer(new CountDownTimer()),
	NewScore(false),
	mGOverGra(new Renderer("GameOver")),
	mChoiceGra(new Renderer("Choice")),
	mClear1(new Renderer("Result1")),
	mClear2(new Renderer("Result2")),
	mC(false),
	HiGra(new Renderer("HIScore")),
	mGra(new Renderer("Background"))
{
	choice = e_restart;
	clear = SceneManager::gameClear;
	//clear = true;
}

Ending::~Ending()
{
	sound->StopBGM("./Assets/Sound/Result.mp3");
	sound->StopBGM("./Assets/Sound/GameOver.mp3");

	sound->DeleteM("./Assets/Sound/kettei.wav");
	sound->DeleteM("./Assets/Sound/migration.wav");
	sound->DeleteM("./Assets/Sound/Result.mp3");
	sound->DeleteM("./Assets/Sound/GameOver.mp3");

	delete(input);
	delete(mNumber);
	delete(timer);
	delete(mGOverGra);
	delete(mChoiceGra);
	delete(mClear1);
	delete(mClear2);
	delete(mBigNumber);
	delete(HiGra);
	delete(mGra);
	delete(sound);
}

void Ending::Init()
{
	numScore = 0;
	timeScore = 0;
	input->Init();
	input->JoyInit();
	sound->Init();
	sound->Load("./Assets/Sound/kettei.wav");
	sound->Load("./Assets/Sound/migration.wav");
	sound->Load("./Assets/Sound/Result.mp3");//クリア
	sound->Load("./Assets/Sound/GameOver.mp3");//ゲームオーバー
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
		//std::string stage;
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
	//NewScore = true;
}

void Ending::Update()
{
	if (clear)
	{
		sound->PlayBGM("./Assets/Sound/Result.mp3");
	}
	else
	{
		sound->PlayBGM("./Assets/Sound/GameOver.mp3");
	}

	input->JoyUpdate();
	timer->Update();
	if (!timer->IsTime())return;
	if (input->GetKeyDown(B) || input->PadDown(Joy_B))
	{
		if (!mC&&clear)
		{
			mC = true;
			timer->SetTime(0.3f);
			return;
		}
		sound->PlaySE("./Assets/Sound/kettei.wav");
		NextScene();
	}
	if (!mC && clear)return;
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
	mGra->Drawb(0, 0);
	if (clear)
	{
		//int figure;//タイムの秒数(整数)
		//figure = SceneManager::mElapsedTime->Now();
		//for (auto count = 1;; ++count)
		//{
		//	if (figure < 10)
		//	{
		//		figure = count;//桁数になる
		//		//continue;
		//		break;
		//	}
		//	figure /= 10;
		//}

		if (mC)
		{
			mClear2->Drawb(0, 0);

			int y;
			switch (choice)
			{
			case e_select:
				y = 320;
				break;
			case e_restart:
				y = 80;
				break;
			}

			mChoiceGra->Drawb(320, y);
		}
		else
		{
			mClear1->Drawb(0, 0);
			mNumber->DrawIntegerNumber(Vector2(500, 110), SceneManager::score);//ゲームによるスコア表示
			//mNumber->DrawNumber(Vector2(396 - (32 * figure), 200), SceneManager::mElapsedTime->Now());//かかった時間表示
			mNumber->DrawIntegerNumber(Vector2(500, 180), timeScore);//タイムによるスコア表示
			//mNumber->DrawIntegerNumber(Vector2(300, 400), numScore);//合計スコア表示
			SetDrawBright(255, 0, 0);
			mBigNumber->DrawBigNumber(Vector2(300, 400), numScore, 64);//合計スコア表示
			if (NewScore)
			{
				//DrawString(380, 300, "ハイスコア更新！！", GetColor(255, 255, 255));
				SetDrawBright(255, 255, 0);
				HiGra->Drawb(600, 450);
			}
			SetDrawBright(255, 255, 255);
		}
	}
	else
	{
		//DrawString(380, 50, "ゲームオーバー", Cr);
		mGOverGra->Drawb(0, 0);

		int y;
		switch (choice)
		{
		case e_select:
			y = 320;
			break;
		case e_restart:
			y = 80;
			break;
		}

		mChoiceGra->Drawb(320, y);
	}
	
	
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
