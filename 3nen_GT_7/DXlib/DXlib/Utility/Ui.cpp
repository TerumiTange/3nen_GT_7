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

//gauzesize>>減少値
void UI::Update(int gauzesize)
{
	//trueだったら長さを求める
	if (active)
	{
		mVolum = mMaxVolum - gauzesize;
	}
}

//描画（画像があったら要書き換え）
void UI::Draw()
{
	//trueならゲージを表示
	if (active)
	{
		DrawBox(50, 50, mMaxVolum, 100, GetColor(0, 255, 0), FALSE);
		DrawBox(50, 50, mVolum, 100, GetColor(0, 255, 0), TRUE);
	}
}