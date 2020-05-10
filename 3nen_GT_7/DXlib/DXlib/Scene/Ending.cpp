#include "Ending.h"
#include "SceneManager.h"

Ending::Ending(ISceneChanger * changer) :
	BaseScene(changer),
	input(new Input()),
	mNumber(new Renderer("Number")),
	sound(new Sound()),
	timer(new CountDownTimer())
{
	t = 250;
	s = 300;
	r = 350;
	choice = e_title;
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

	if (input->GetKeyDown(S) || input->GetKeyDown(DOWNARROW) || input->PadDown(JoyCode::Joy_Down))//��
	{
		choice = (choice + 1) % endNum;//1������
		timer->SetTime(0.3f);
		return;
	}
	if (input->GetKeyDown(W) || input->GetKeyDown(UPARROW) || input->PadDown(JoyCode::Joy_Up))
	{
		choice = (choice + (endNum - 1)) % endNum;//1�グ��
		timer->SetTime(0.3f);
		return;
	}

	if (input->Vertical() > 0)
	{
		choice = (choice + 1) % endNum;//1������
		timer->SetTime(0.3f);
		return;
	}
	if (input->Vertical() < 0)
	{
		choice = (choice + (endNum - 1)) % endNum;//1�グ��
		timer->SetTime(0.3f);
		return;
	}

}

void Ending::Draw()
{
	int Cr = GetColor(255, 0, 0);
	SetFontSize(32);
	DrawString(380, 50, "�Q�[���N���A", Cr);
	mNumber->DrawNumber(Vector2(400, 100), SceneManager::mElapsedTime->Now());//�����������ԕ\��
	DrawString(380, 150, "�����ɃX�R�A������\��", Cr);
	DrawString(380, 200, "�����ɍ��v�X�R�A������\��", Cr);
	DrawString(380, t, "�^�C�g����", Cr);
	DrawString(380, s, "�Q�[���Z���N�g��", Cr);
	DrawString(380, r, "������x�����X�e�[�W�ŗV��", Cr);
	DrawString(0, 0, "B PUSH", Cr);
	int y;
	switch (choice)
	{
	case e_title:
		y = t;
		break;
	case e_select:
		y = s;
		break;
	case e_restart:
		y = r;
		break;
	}
	DrawString(300, y, "��", GetColor(0, 255, 0));
}

void Ending::NextScene()
{
	switch (choice)
	{
	case e_title:
		mSceneChanger->ChangeScene(SceneTitle);
		break;
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
