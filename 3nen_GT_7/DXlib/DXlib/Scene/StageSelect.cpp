#include "StageSelect.h"

StageSelect::StageSelect(ISceneChanger* changer):
	BaseScene(changer),
	mInput(new Input()),
	mTimers(new CountDownTimer()),
	stage1Pos(new Vector2(100,100)),
	stage2Pos(new Vector2(200,100)),
	stage3Pos(new Vector2(300,100)),
	stage4Pos(new Vector2(100,150)),
	stage5Pos(new Vector2(200,150)),
	stage6Pos(new Vector2(300,150)),
	sound(new Sound())
{
	choice = stage1;//最初はステージ1
	
}

StageSelect::~StageSelect()
{
	delete(mInput);
	delete(mTimers);
	delete(stage1Pos);
	delete(stage2Pos);
	delete(stage3Pos);
	delete(stage4Pos);
	delete(stage5Pos);
	delete(stage6Pos);
}

void StageSelect::Init()
{
	mInput->Init();
	sound->Init();
	sound->Load("./Assets/Sound/kettei.wav");
	sound->Load("./Assets/Sound/migration.wav");
}

void StageSelect::Update()
{
	mInput->JoyUpdate();
	mTimers->Update();

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
		break;
	case stage2:
		xy = *stage2Pos;
		break;
	case stage3:
		xy = *stage3Pos;
		break;
	case stage4:
		xy = *stage4Pos;
		break;
	case stage5:
		xy = *stage5Pos;
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
		SceneManager::stageName = "map";
		break;
	case stage2:
		SceneManager::stageName = "map";
		break;
	case stage3:
		SceneManager::stageName = "map";
		break;
	case stage4:
		SceneManager::stageName = "rei";
		break;
	case stage5:
		SceneManager::stageName = "stage1";
		break;
	case stage6:
		mSceneChanger->ChangeScene(SceneTitle);
		return;
	}
	mSceneChanger->ChangeScene(SceneGamePlay);
}
