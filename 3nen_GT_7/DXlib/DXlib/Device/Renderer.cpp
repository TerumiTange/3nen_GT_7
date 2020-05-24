
#include "Renderer.h"
#include "Camera2d.h"

#define PI 3.1415926535897932384626433832795f

Renderer::Renderer(const char* name):
	mName("./Assets/Texture/"),
	mGra(0),
	width(32)
{
	mName = mName + name + ".png";
	mGra = LoadGraph(mName.c_str());
}

Renderer::~Renderer()
{
	DeleteGraph(mGra);
}

void Renderer::Init()
{
	//mName = "./Assets/Texture/";//Main.h�ł̕`��p	
	mName = "./Assets/Texture/";
}

void Renderer::Draw(const Vector2 & pos)
{
	DrawGraph(pos.x - Camera2d::CameraPos.x, pos.y - Camera2d::CameraPos.y, mGra, TRUE);
}

void Renderer::Draw(int x, int y)
{
	DrawGraph(x - Camera2d::CameraPos.x, y - Camera2d::CameraPos.y, mGra, TRUE);
}

void Renderer::Drawb(int x, int y)
{
	DrawGraph(x, y, mGra, TRUE);
}

void Renderer::DrawE(const Vector2 & pos, int e)
{
	//DrawGraph(pos.x - Camera2d::CameraPos.x, pos.y - Camera2d::CameraPos.y, mGra, TRUE);
	DrawExtendGraph(pos.x - Camera2d::CameraPos.x, pos.y - Camera2d::CameraPos.y, pos.x - Camera2d::CameraPos.x+e, pos.y - Camera2d::CameraPos.y+e, mGra, TRUE);
}

void Renderer::DrawIntegerNumber(const Vector2 & pos, int num)//Numver�̂ݎg�p�ł���
{
	if (num < 0)
	{
		num = 0;
	}
	int x = pos.x;
	std::string n = std::to_string(num);
	for (auto a : n)
	{
		DrawRectGraph(x, pos.y, (a - '0')*width, 0, 32, 32, mGra, TRUE, FALSE);
		x += width;
	}
}

void Renderer::DrawNumber(const Vector2& pos, float num)//Number�̂ݎg�p�ł���
{
	SetDrawBright(255, 0, 0);
	if (num < 0.f)//�}�C�i�X�Ȃ�0��
	{
		num = 0.f;
	}
	int x = pos.x;
	std::string n = std::to_string(num);
	bool bbb = false;
	int count = 0;
	for (auto a : n)
	{
		if (a == '.')//.�̕`��
		{
			DrawRectGraph(x, pos.y, 10 * width, 0, 32, 32, mGra, TRUE, FALSE);
			bbb = true;
		}
		else//�����̕`��
		{
			DrawRectGraph(x, pos.y, (a - '0')*width, 0, 32, 32, mGra, TRUE, FALSE);
			if (bbb)count++;
		}
		x += width;
		if (count >= 2)break;
	}
	SetDrawBright(255, 255, 255);
}

//�`��ʒu�A�摜�̊J�n�ʒu�A�����ڂ̕`�悩�A�`��͈́A���]���邩�ǂ����iTRUE�Ȃ甽�]�j
void Renderer::DrawSerialNumber(const Vector2& pos, const Vector2& gPos, int t, const Vector2& size, bool turnFlag)
{
	
	DrawRectGraph(pos.x - Camera2d::CameraPos.x, pos.y - Camera2d::CameraPos.y, gPos.x + size.x * t, gPos.y, size.x, size.y, mGra, TRUE, turnFlag);

}
