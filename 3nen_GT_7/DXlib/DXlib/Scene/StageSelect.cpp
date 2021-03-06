#include "StageSelect.h"
#include <iostream>
#include <fstream>

StageSelect::StageSelect(ISceneChanger* changer):
	BaseScene(changer),
	mInput(new Input()),
	mTimers(new CountDownTimer()),
	stage1Pos(new Vector2(48,352)),
	stage2Pos(new Vector2(208,352)),
	stage3Pos(new Vector2(368,352)),
	stage4Pos(new Vector2(528,352)),
	stage5Pos(new Vector2(688,352)),
	stage6Pos(new Vector2(848,352)),
	mBack(new Renderer("StageSelect")),
	mRenderer(new Renderer("Number")),
	mSelect(new Renderer("Select")),
	mStage1(new Renderer("stage1")),
	mStage2(new Renderer("stage2")),
	mStage3(new Renderer("stage3")),
	mStage4(new Renderer("stage4")),
	mStage5(new Renderer("stage5")),
	title(new Renderer("title")),
	sound(new Sound())
{
	choice = stage1;//最初はステージ1
	
}

StageSelect::~StageSelect()
{
	sound->StopBGM("./Assets/Sound/Title.mp3");//BGM
	sound->DeleteM("./Assets/Sound/kettei.wav");
	sound->DeleteM("./Assets/Sound/migration.wav");
	sound->DeleteM("./Assets/Sound/Title.mp3");//BGM
	delete(mInput);
	delete(mTimers);
	delete(stage1Pos);
	delete(stage2Pos);
	delete(stage3Pos);
	delete(stage4Pos);
	delete(stage5Pos);
	delete(stage6Pos);
	delete(mBack);
	delete(mSelect);
	delete(mRenderer);
	delete(mStage1);
	delete(mStage2);
	delete(mStage3);
	delete(mStage4);
	delete(mStage5);
	delete(sound);
	delete(title);
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

}

void StageSelect::Draw()
{
	mBack->Drawb(0, 0);
	//int Cr = GetColor(255, 0, 0);
	//SetFontSize(32);
	//DrawString(50, 50, "ステージ選択", Cr);
	//DrawString(stage1Pos->x, stage1Pos->y, "ステージ1", Cr);
	//DrawString(stage2Pos->x, stage2Pos->y, "ステージ2", Cr);
	//DrawString(stage3Pos->x, stage3Pos->y, "ステージ3", Cr);
	//DrawString(stage4Pos->x, stage4Pos->y, "ステージ4", Cr);
	//DrawString(stage5Pos->x, stage5Pos->y, "ステージ5", Cr);
	//DrawString(stage6Pos->x, stage6Pos->y, "タイトルへ", Cr);
	//DrawString(50, 150, "最高スコア", Cr);
	

	switch (choice)
	{
	case stage1:
		mSelect->Drawb(stage1Pos->x, stage1Pos->y);
		mRenderer->DrawIntegerNumber(Vector2(512, 250), Score1);
		mStage1->Drawb(302, 100);
		break;
	case stage2:
		mSelect->Drawb(stage2Pos->x, stage2Pos->y);
		mRenderer->DrawIntegerNumber(Vector2(512, 250), Score2);
		mStage2->Drawb(352, 100);
		break;
	case stage3:
		mSelect->Drawb(stage3Pos->x, stage3Pos->y);
		mRenderer->DrawIntegerNumber(Vector2(512, 250), Score3);
		mStage3->Drawb(352, 100);
		break;
	case stage4:
		mSelect->Drawb(stage4Pos->x, stage4Pos->y);
		mRenderer->DrawIntegerNumber(Vector2(512, 250), Score4);
		mStage4->Drawb(352, 100);
		break;
	case stage5:
		mSelect->Drawb(stage5Pos->x, stage5Pos->y);
		mRenderer->DrawIntegerNumber(Vector2(512, 250), Score5);
		mStage5->Drawb(352, 100);
		break;
	case stage6:
		mSelect->Drawb(stage6Pos->x, stage6Pos->y);
		title->Drawb(352, 100);
		break;
	}
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
