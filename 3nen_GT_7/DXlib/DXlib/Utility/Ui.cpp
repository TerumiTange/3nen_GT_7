#include "Ui.h"

//コンスト（場所、大きさ、画像）
UI::UI(const Vector2 &position, const Vector2 &size,const int &maxValum, int texture) :mPos(new Vector2()), mSize(new Vector2()), mMaxVolum(), mTexture()
{
	
}

UI::~UI()
{}

//初期化
void UI::Init()
{
	active = true;
	mVolum = 0;
}

//表示非表示
void UI::Active(bool set)
{
	active = set;
}


//描画（画像があったら要書き換え）

//ゲージ(現在の値、最大値)
void UI::Gauge(int volum,int maxVolum)
{
	//trueならゲージを表示
	if (active)
	{
		DrawBox(50, 50, mMaxVolum, 100, GetColor(0, 255, 0), FALSE);
		DrawBox(50, 50, mVolum, 100, GetColor(0, 255, 0), TRUE);
	}
}

//ゼルダの体力みたいなやつ(現在の値、最大値)
void UI::Cell(int volum, int maxVolum)
{
	for (int i = 0; i < maxVolum + 1; i++)
	{
		DrawCircle(mPos->x + 32 * i, mPos->y, GetColor(0, 127, 255), false);
	}

	if (volum < maxVolum)
	{
		for (int i = 0; i < volum + 1; i++)
		{
			DrawCircle(mPos->x + 32 * i, mPos->y, GetColor(0, 127, 255), true);
		}
	}
}
