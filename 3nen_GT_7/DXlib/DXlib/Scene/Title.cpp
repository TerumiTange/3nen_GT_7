#include "Title.h"
#include "DxLib.h"

Title::Title(ISceneChanger* changer)
	:BaseScene(changer),
	input(new Input()),
	startY(100),
	creditY(150),
	configFllY(200),
	configModeY(250),
	timer(new CountDownTimer())
{
	choice = start;//�ŏ��̓Q�[���X�^�[�g��I��
}

Title::~Title()
{
	delete(input);
	delete(timer);
}

void Title::Init()
{
	input->Init();
}

void Title::Update()
{
	input->JoyUpdate();
	timer->Update();

	if (input->GetKeyDown(B) || input->PadDown(Joy_B))
	{
		NextScene();
	}
	if (!timer->IsTime())return;
	if (input->GetKeyDown(S) || input->GetKeyDown(DOWNARROW) || input->PadDown(JoyCode::Joy_Down) || (input->Vertical() < 0))//��
	{
		choice = (choice + 1) % eMenuNum;//1������
		timer->SetTime(0.2f);
	}
	if (input->GetKeyDown(W) || input->GetKeyDown(UPARROW) || input->PadDown(JoyCode::Joy_Up) || (input->Vertical() > 0))
	{
		choice = (choice + (eMenuNum - 1)) % eMenuNum;//1�グ��
		timer->SetTime(0.2f);
	}
}

void Title::Draw()
{
	int Cr = GetColor(255, 0, 0);
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
		mSceneChanger->ChangeScene(SceneGamePlay);
		break;
	case credit:
		//mSceneChanger->ChangeScene(SceneCredit);
		mSceneChanger->ChangeScene(SceneGamePlay);
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
