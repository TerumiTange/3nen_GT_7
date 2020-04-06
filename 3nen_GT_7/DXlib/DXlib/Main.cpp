
#include "Device/Dx.h"
#include "Device/Renderer.h"
#include "Scene/GamePlay.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GamePlay mGame;
	// ウインドウモードで起動
	ChangeWindowMode(TRUE);
	// ウインドウのサイズを手動ではできず、且つウインドウのサイズに合わせて拡大もしないようにする
	//SetWindowSizeChangeEnableFlag(TRUE, TRUE);
	// 画面サイズは最大の 1920x1080 にしておく
	SetGraphMode(1920, 1080, 32);
	// 最初は 640x480 にしておく
	SetWindowSize(1024,576);//16:9//1024:576

	SetMainWindowText("ばっきゃろ～");

	SetDrawScreen(DX_SCREEN_BACK);

	// 垂直同期信号を待たない
	SetWaitVSyncFlag(FALSE);

	// ６０ＦＰＳ固定用、時間保存用変数を現在のカウント値にセット
	int FrameStartTime = GetNowCount();
	
	if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
	{
		return -1;    // エラーが起きたら直ちに終了
	}

	mGame.Init();


	// メインループ(何かキーが押されたらループを抜ける)
	while (ProcessMessage() == 0)
	{
		// 画面のクリア
		ClearDrawScreen();

		// １/６０秒立つまで待つ
		while (GetNowCount() - FrameStartTime < 1000 / 60) {}
		// 現在のカウント値を保存
		FrameStartTime = GetNowCount();

		mGame.Update();
		mGame.Draw();
		
		if (WaitKey())
		{
			//break;
		}
		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}
	/*// キーが押されるまでループします
	// (因みにキーが押されるまで待つ事は『WaitKey』という専用の関数があります)
	while (CheckHitKeyAll() == 0)
	{
		// メッセージループに代わる処理をする
		if (ProcessMessage() == -1)
		{
			break;        // エラーが起きたらループを抜ける
		}
	}*/
	
	DxLib_End();        // ＤＸライブラリ使用の終了処理

	return 0;        // ソフトの終了
}