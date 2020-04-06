
#include "Device/Dx.h"
#include "Device/Renderer.h"
#include "Scene/GamePlay.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GamePlay mGame;
	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);
	// �E�C���h�E�̃T�C�Y���蓮�ł͂ł����A���E�C���h�E�̃T�C�Y�ɍ��킹�Ċg������Ȃ��悤�ɂ���
	//SetWindowSizeChangeEnableFlag(TRUE, TRUE);
	// ��ʃT�C�Y�͍ő�� 1920x1080 �ɂ��Ă���
	SetGraphMode(1920, 1080, 32);
	// �ŏ��� 640x480 �ɂ��Ă���
	SetWindowSize(1024,576);//16:9//1024:576

	SetMainWindowText("�΂������`");

	SetDrawScreen(DX_SCREEN_BACK);

	// ���������M����҂��Ȃ�
	SetWaitVSyncFlag(FALSE);

	// �U�O�e�o�r�Œ�p�A���ԕۑ��p�ϐ������݂̃J�E���g�l�ɃZ�b�g
	int FrameStartTime = GetNowCount();
	
	if (DxLib_Init() == -1)    // �c�w���C�u��������������
	{
		return -1;    // �G���[���N�����璼���ɏI��
	}

	mGame.Init();


	// ���C�����[�v(�����L�[�������ꂽ�烋�[�v�𔲂���)
	while (ProcessMessage() == 0)
	{
		// ��ʂ̃N���A
		ClearDrawScreen();

		// �P/�U�O�b���܂ő҂�
		while (GetNowCount() - FrameStartTime < 1000 / 60) {}
		// ���݂̃J�E���g�l��ۑ�
		FrameStartTime = GetNowCount();

		mGame.Update();
		mGame.Draw();
		
		if (WaitKey())
		{
			//break;
		}
		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}
	/*// �L�[���������܂Ń��[�v���܂�
	// (���݂ɃL�[���������܂ő҂��́wWaitKey�x�Ƃ�����p�̊֐�������܂�)
	while (CheckHitKeyAll() == 0)
	{
		// ���b�Z�[�W���[�v�ɑ��鏈��������
		if (ProcessMessage() == -1)
		{
			break;        // �G���[���N�����烋�[�v�𔲂���
		}
	}*/
	
	DxLib_End();        // �c�w���C�u�����g�p�̏I������

	return 0;        // �\�t�g�̏I��
}