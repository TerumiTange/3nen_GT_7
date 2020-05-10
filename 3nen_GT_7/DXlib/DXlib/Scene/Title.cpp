#include "Title.h"
#include "DxLib.h"

Title::Title(ISceneChanger* changer)
	:BaseScene(changer),
	input(new Input()),
	startY(100),
	creditY(150),
	configFllY(200),
	configModeY(250),
	timer(new CountDownTimer()),
	sound(new Sound())
{
	choice = start;//�ŏ��̓Q�[���X�^�[�g��I��
}

Title::~Title()
{
	delete(input);
	delete(timer);
	delete(sound);
}

void Title::Init()
{
	input->Init();
	sound->Init();
	sound->Load("./Assets/Sound/kettei.wav");
}

void Title::Update()
{
	input->JoyUpdate();
	timer->Update();


	if (input->GetKeyDown(B) || input->PadDown(Joy_B))
	{
		sound->PlaySE("./Assets/Sound/kettei.wav");
		NextScene();
	}
	if (!timer->IsTime())return;
	if (input->GetKeyDown(S) || input->GetKeyDown(DOWNARROW) || input->PadDown(JoyCode::Joy_Down))//��
	{
		choice = (choice + 1) % eMenuNum;//1������
		timer->SetTime(0.3f);
		return;
	}
	if (input->GetKeyDown(W) || input->GetKeyDown(UPARROW) || input->PadDown(JoyCode::Joy_Up))
	{
		choice = (choice + (eMenuNum - 1)) % eMenuNum;//1�グ��
		timer->SetTime(0.3f);
		return;
	}

	if (input->Vertical() > 0)
	{
		choice = (choice + 1) % eMenuNum;//1������
		timer->SetTime(0.3f);
		return;
	}
	if (input->Vertical() < 0)
	{
		choice = (choice + (eMenuNum - 1)) % eMenuNum;//1�グ��
		timer->SetTime(0.3f);
		return;
	}
}

void Title::Draw()
{
	int Cr = GetColor(255, 0, 0);
	SetFontSize(16);
	DrawString(150, 50, "Title B PUSH�@�ǂ����I��ł��Q�[���v���C�ɍs�����ǂ�", Cr);
	DrawString(150, startY, "�X�^�[�g", Cr);
	DrawString(150, creditY, "�N���W�b�g", Cr);
	DrawString(150, configFllY, "�t���X�N���[���ɂ���", Cr);
	DrawString(150, configModeY, "�E�B���h�E���[�h�ɂ���", Cr);
	int y;
	switch (choice)
	{
	case start:
		y = startY;
		break;
	case credit:
		y = creditY;
		break;
	case full:
		y = configFllY;
		break;
	case mode:
		y = configModeY;
		break;
	}
	DrawString(100, y, "��", GetColor(0, 255, 0));
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
	case full:
		ChangeWindowMode(FALSE);
		SetWaitVSyncFlag(TRUE);
		DxLib_Init();
		SetDrawScreen(DX_SCREEN_BACK);
		break;
	case mode:
		ChangeWindowMode(TRUE);
		SetWaitVSyncFlag(FALSE);
		DxLib_Init();
		SetDrawScreen(DX_SCREEN_BACK);
		break;
	default:
	  mSceneChanger->ChangeScene(SceneSelect);//��O������������
		break;
	}
	//mSceneChanger->ChangeScene(SceneGamePlay);
}
