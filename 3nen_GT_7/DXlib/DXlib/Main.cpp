#include "Device/Dx.h"
#include "Scene/SceneManager.h"
#include "Device/WindowSize.h"
#include "System/Input.h"
//static int ScreenWidth = 1024;
//static int ScreenHeight = 576;
#include <crtdbg.h>

class Fps
{
public:
	Fps()
	{
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}
	bool Update()
	{
		if (mCount == 0)//1�t���[���ڂȂ玞�����L��
		{
			mStartTime = GetNowCount();
		}
		if (mCount == N)//60�t���[���ڂȂ畽�ς��v�Z����
		{
			int t = GetNowCount();
			mFps = 1000.f / ((t - mStartTime) / (float)N);
			mCount = 0;
			mStartTime = t;
		}
		mCount++;
		return true;
	}
	void Draw()
	{
		DrawFormatString(0, 0, GetColor(255, 0, 0), "%.1f", mFps);
		clsDx();
		printfDx("%.1f", mFps);
	}
	void Wait()
	{
		int tookTime = GetNowCount() - mStartTime;
		int waitTime = mCount * 1000 / FPS - tookTime;
		if (waitTime > 0)
		{
			Sleep(waitTime);
		}
	}

private:
	int mStartTime;//�v���J�n����
	int mCount;//�J�E���^
	float mFps;//fps
	static const int N = 60;//���ς��Ƃ�T���v����
	static const int FPS = 60;//�ݒ肷��FPS�̒l
};

void message_box()
{
	int flag;
	flag = MessageBox(
		NULL,
		TEXT("�R���g���[���[���ڑ�����Ă��܂���B�Q�[�����I�����܂�"),
		TEXT("�R���g���[���[�ݒ�"),
		//MB_YESNO | MB_ICONQUESTION);
		NULL);
	//if (flag == IDNO)
	//{
	//	ChangeWindowMode(TRUE);
	//	SetWaitVSyncFlag(TRUE);
	//}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//�������[���[�N���o
	//_CrtSetBreakAlloc(15679);//�������[���[�N���o����()�ɐ���������

	bool g = true;
	int a = GetJoypadNum();
	if (GetJoypadNum() != 0)
	{
		g = false;
	}

	if (g)
	{
		message_box();
	}
	else
	{
		// ���������M����҂��Ȃ�
		SetWaitVSyncFlag(FALSE);

		// �E�C���h�E���[�h�ŋN��
		ChangeWindowMode(TRUE);

		// �E�C���h�E�̃T�C�Y���蓮�ł͂ł����A���E�C���h�E�̃T�C�Y�ɍ��킹�Ċg������Ȃ��悤�ɂ���
		//SetWindowSizeChangeEnableFlag(TRUE, TRUE);
		// ��ʃT�C�Y�͍ő�� 1920x1080 �ɂ��Ă���
		SetGraphMode(1024, 576, 32);
		// �ŏ��� 640x480 �ɂ��Ă���
		//SetWindowSize(ScreenWidth,ScreenHeight);//16:9//1024:576

		SetMainWindowText("VOLT CHAIN");


		//�w�i�F��ύX
		SetBackgroundColor(0, 0, 0);


		//���Ƃ�Window�T�C�Y��ύX���Ă����Ȃ��悤�ɂ���
		//MakeScreen()
		//SetDrawMode(DX_DRAWMODE_BILINEAR);
		//DrawExtendGraph()
		//ScreenFlip()

		// �U�O�e�o�r�Œ�p�A���ԕۑ��p�ϐ������݂̃J�E���g�l�ɃZ�b�g
		//int FrameStartTime = GetNowCount();
		Fps fps;


		if (DxLib_Init() == -1)    // �c�w���C�u��������������
		{
			return -1;    // �G���[���N�����璼���ɏI��
		}
		SetDrawScreen(DX_SCREEN_BACK);
		SceneManager manager;
		manager.Init();
		Input* input = new Input();
		input->JoyInit();

		// ���C�����[�v(�����L�[�������ꂽ�烋�[�v�𔲂���)
		while (ProcessMessage() == 0 && !g)//ProcessMessage()
		{
			input->JoyUpdate();
			if ((input->PadDown(JoyCode::Joy_R1)) && (input->PadDown(JoyCode::Joy_L1)) && (input->PadDown(JoyCode::Joy_Start)) && (input->PadDown(JoyCode::Joy_Back)))
			{
				break;
			}
			// �P/�U�O�b���܂ő҂�
			//while (GetNowCount() - FrameStartTime < 1000 / 60) {}
			// ���݂̃J�E���g�l��ۑ�
			//FrameStartTime = GetNowCount();
			if (input->GetKeyDown(ESCAPE))//ESC�ŃE�B���h�E�����
			{
				break;
			}

			fps.Update();//�X�V
			fps.Draw();//���݂�FPS��`��

			// ��ʂ̃N���A
			ClearDrawScreen();


			manager.Update();
			manager.Draw();

			fps.Wait();//�ҋ@

			// ����ʂ̓��e��\��ʂɔ��f
			ScreenFlip();
		}

		delete(input);
	}
	DxLib_End();      // �c�w���C�u�����g�p�̏I������

	return 0;        // �\�t�g�̏I��
}
