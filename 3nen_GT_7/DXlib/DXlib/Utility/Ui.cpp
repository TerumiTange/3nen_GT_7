#include "Ui.h"

//�R���X�g�i�ꏊ�A�傫���A�摜�j
UI::UI(const Vector2 &position, const Vector2 &size,const int &maxValum, int texture) :mPos(new Vector2()), mSize(new Vector2()), mMaxVolum(), mTexture()
{
	
}

UI::~UI()
{}

//������
void UI::Init()
{
	active = true;
	mVolum = 0;
}

//�\����\��
void UI::Active(bool set)
{
	active = set;
}


//�`��i�摜����������v���������j

//�Q�[�W(���݂̒l�A�ő�l)
void UI::Gauge(int volum,int maxVolum)
{
	//true�Ȃ�Q�[�W��\��
	if (active)
	{
		DrawBox(50, 50, mMaxVolum, 100, GetColor(0, 255, 0), FALSE);
		DrawBox(50, 50, mVolum, 100, GetColor(0, 255, 0), TRUE);
	}
}

//�[���_�̗݂̑͂����Ȃ��(���݂̒l�A�ő�l)
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
