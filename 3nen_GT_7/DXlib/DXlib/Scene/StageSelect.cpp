#include "StageSelect.h"
#include <iostream>
#include <fstream>

StageSelect::StageSelect(ISceneChanger* changer):
	BaseScene(changer),
	mInput(new Input()),
	mTimers(new CountDownTimer()),
	stage1Pos(new Vector2(700,100)),
	stage2Pos(new Vector2(800,100)),
	stage3Pos(new Vector2(900,100)),
	stage4Pos(new Vector2(700,150)),
	stage5Pos(new Vector2(800,150)),
	stage6Pos(new Vector2(900,150)),
	sound(new Sound())
{
	choice = stage1;//最初はステージ1
	
}

StageSelect::~StageSelect()
{
	sound->StopBGM("./Assets/Sound/Title.mp3");//BGM
	delete(mInput);
	delete(mTimers);
	delete(stage1Pos);
	delete(stage2Pos);
	delete(stage3Pos);
	delete(stage4Pos);
	delete(stage5Pos);
	delete(stage6Pos);
	delete(sound);
}

void StageSelect::CSVReader()
{
	//std::ifstream fileOpen("./Assets/Data/Score1.txt");//読み込み
	//std::string s;
	//std::getline(fileOpen, s);
	//fileOpen.close();
	//Score1 = atoi(s.c_str());//string → int 

	Score1 = SceneManager::mScore->Load("./Assets/Data/Score1.txt");
	Score2 = SceneManager::mScore->Load("./Assets/Data/Score2.txt");
	Score3 = SceneManager::mScore->Load("./Assets/Data/Score3.txt");
	Score4 = SceneManager::mScore->Load("./Assets/Data/Score4.txt");
	Score5 = SceneManager::mScore->Load("./Assets/Data/Score5.txt");

	/*
	std::string ss;
	ss = std::to_string(num);//int → string


	std::ofstream fileWrite("./Assets/Data/Score1.txt");//書き込み
	fileWrite << ss;
	fileWrite.close();
	*/
}

void StageSelect::Init()
{
	CSVReader();
	mInput->Init();
	sound->Init();
	sound->Load("./Assets/Sound/kettei.wav");
	sound->Load("./Assets/Sound/migration.wav");
	sound->Load("./Assets/Sound/Title.mp3");//BGM
}

void StageSelect::Update()
{
	mInput->JoyUpdate();
	mTimers->Update();
	sound->PlayBGM("./Assets/Sound/Title.mp3");
	if (mInput->PadDown(JoyCode::Joy_B) || mInput->GetKeyDown(B))
	{
		sound->PlaySE("./Assets/Sound/kettei.wav");
		NextScene();
	}

	if (!mTimers->IsTime())return;

	if (mInput->GetKeyDown(D) || mInput->GetKeyDown(RIGHTARROW) || mInput->PadDown(JoyCode::Joy_Right))//右
	{
		sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + 1) % eStageNum;
		mTimers->SetTime(0.3f);
		return;
	}

	if (mInput->GetKeyDown(A) || mInput->GetKeyDown(LEFTARROW) || mInput->PadDown(JoyCode::Joy_Left))//左
	{
		sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + (eStageNum - 1)) % eStageNum;
		mTimers->SetTime(0.3f);
		return;
	}

	if (mInput->GetKeyDown(W) || mInput->GetKeyDown(UPARROW) || mInput->PadDown(JoyCode::Joy_Up))//上
	{
		sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + (eStageNum - 3)) % eStageNum;
		mTimers->SetTime(0.3f);
		return;
	}

	if (mInput->GetKeyDown(S) || mInput->GetKeyDown(DOWNARROW) || mInput->PadDown(JoyCode::Joy_Down))//下
	{
		sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + 3) % eStageNum;
		mTimers->SetTime(0.3f);
		return;
	}


	if (mInput->Horizontal() > 0)//右
	{
		sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + 1) % eStageNum;
		mTimers->SetTime(0.3f);
		return;
	}
	if (mInput->Horizontal() < 0)//左
	{
		sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + (eStageNum - 1)) % eStageNum;
		mTimers->SetTime(0.3f);
		return;
	}

	if (mInput->Vertical() > 0)//上
	{
		sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + (eStageNum - 3)) % eStageNum;
		mTimers->SetTime(0.3f);
		return;
	}

	if (mInput->Vertical() > 0)//下
	{
		sound->PlaySE("./Assets/Sound/migration.wav");
		choice = (choice + 3) % eStageNum;
		mTimers->SetTime(0.3f);
		return;
	}
}

void StageSelect::Draw()
{
	int Cr = GetColor(255, 0, 0);
	SetFontSize(16);
	DrawString(50, 50, "ステージ選択", Cr);
	DrawString(stage1Pos->x, stage1Pos->y, "ステージ1", Cr);
	DrawString(stage2Pos->x, stage2Pos->y, "ステージ2", Cr);
	DrawString(stage3Pos->x, stage3Pos->y, "ステージ3", Cr);
	DrawString(stage4Pos->x, stage4Pos->y, "ステージ4", Cr);
	DrawString(stage5Pos->x, stage5Pos->y, "ステージ5", Cr);
	DrawString(stage6Pos->x, stage6Pos->y, "タイトルへ", Cr);

	

	Vector2 xy;
	switch (choice)
	{
	case stage1:
		xy = *stage1Pos;
		DrawFormatString(50, 150, Cr, "%d", Score1);
		break;
	case stage2:
		xy = *stage2Pos;
		DrawFormatString(50, 150, Cr, "%d", Score2);
		break;
	case stage3:
		xy = *stage3Pos;
		DrawFormatString(50, 150, Cr, "%d", Score3);
		break;
	case stage4:
		xy = *stage4Pos;
		DrawFormatString(50, 150, Cr, "%d", Score4);
		break;
	case stage5:
		xy = *stage5Pos;
		DrawFormatString(50, 150, Cr, "%d", Score5);
		break;
	case stage6:
		xy = *stage6Pos;
		break;
	}
	DrawString(xy.x - 20, xy.y, "■", GetColor(0, 255, 0));
}

void StageSelect::NextScene()
{
	switch (choice)
	{
	case stage1:
		SceneManager::stageName = "stage1";
		break;
	case stage2:
		SceneManager::stageName = "stage2";
		break;
	case stage3:
		SceneManager::stageName = "stage3";
		break;
	case stage4:
		SceneManager::stageName = "stage4";
		break;
	case stage5:
		SceneManager::stageName = "stage5";
		break;
	case stage6:
		mSceneChanger->ChangeScene(SceneTitle);
		return;
	default:
		SceneManager::stageName = "rei";
	}
	mSceneChanger->ChangeScene(SceneGamePlay);
}
