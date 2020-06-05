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
		if (mCount == 0)//1フレーム目なら時刻を記憶
		{
			mStartTime = GetNowCount();
		}
		if (mCount == N)//60フレーム目なら平均を計算する
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
	int mStartTime;//計測開始時刻
	int mCount;//カウンタ
	float mFps;//fps
	static const int N = 60;//平均をとるサンプル数
	static const int FPS = 60;//設定するFPSの値
};

void message_box()
{
	int flag;
	flag = MessageBox(
		NULL,
		TEXT("コントローラーが接続されていません。ゲームを終了します"),
		TEXT("コントローラー設定"),
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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//メモリーリーク検出
	//_CrtSetBreakAlloc(15679);//メモリーリークが出たら()に数字を入れる

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
		// 垂直同期信号を待たない
		SetWaitVSyncFlag(FALSE);

		// ウインドウモードで起動
		ChangeWindowMode(TRUE);

		// ウインドウのサイズを手動ではできず、且つウインドウのサイズに合わせて拡大もしないようにする
		//SetWindowSizeChangeEnableFlag(TRUE, TRUE);
		// 画面サイズは最大の 1920x1080 にしておく
		SetGraphMode(1024, 576, 32);
		// 最初は 640x480 にしておく
		//SetWindowSize(ScreenWidth,ScreenHeight);//16:9//1024:576

		SetMainWindowText("VOLT CHAIN");


		//背景色を変更
		SetBackgroundColor(0, 0, 0);


		//あとでWindowサイズを変更しても問題ないようにする
		//MakeScreen()
		//SetDrawMode(DX_DRAWMODE_BILINEAR);
		//DrawExtendGraph()
		//ScreenFlip()

		// ６０ＦＰＳ固定用、時間保存用変数を現在のカウント値にセット
		//int FrameStartTime = GetNowCount();
		Fps fps;


		if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
		{
			return -1;    // エラーが起きたら直ちに終了
		}
		SetDrawScreen(DX_SCREEN_BACK);
		SceneManager manager;
		manager.Init();
		Input* input = new Input();
		input->JoyInit();

		// メインループ(何かキーが押されたらループを抜ける)
		while (ProcessMessage() == 0 && !g)//ProcessMessage()
		{
			input->JoyUpdate();
			if ((input->PadDown(JoyCode::Joy_R1)) && (input->PadDown(JoyCode::Joy_L1)) && (input->PadDown(JoyCode::Joy_Start)) && (input->PadDown(JoyCode::Joy_Back)))
			{
				break;
			}
			// １/６０秒立つまで待つ
			//while (GetNowCount() - FrameStartTime < 1000 / 60) {}
			// 現在のカウント値を保存
			//FrameStartTime = GetNowCount();
			if (input->GetKeyDown(ESCAPE))//ESCでウィンドウを閉じる
			{
				break;
			}

			fps.Update();//更新
			fps.Draw();//現在のFPSを描画

			// 画面のクリア
			ClearDrawScreen();


			manager.Update();
			manager.Draw();

			fps.Wait();//待機

			// 裏画面の内容を表画面に反映
			ScreenFlip();
		}

		delete(input);
	}
	DxLib_End();      // ＤＸライブラリ使用の終了処理

	return 0;        // ソフトの終了
}
