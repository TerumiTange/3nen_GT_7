#include "Ui.h"

//コンスト（場所、大きさ、画像）
UI::UI(const Vector2 &position, const Vector2 &size,const int &maxValum, int texture) :mPos(new Vector2()), mSize(new Vector2()), mMaxVolum(), mTexture()
{
	mVolum = 0;
}

UI::~UI()
{}

void UI::Init()
{
	active = true;
}

void UI::Active(bool set)
{
	active = set;
}

//gauzesize>>減少値
void UI::Update(int gauzesize)
{
	if (active)
	{
		mVolum = mMaxVolum - gauzesize;
	}
}

void UI::Draw()
{
	DrawBox(50, 50, mMaxVolum, 100, GetColor(0, 255, 0), FALSE);
	DrawBox(50, 50, mVolum, 100, GetColor(0, 255, 0), TRUE);
}