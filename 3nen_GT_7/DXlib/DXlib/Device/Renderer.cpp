
#include "Renderer.h"
#include "Camera2d.h"

#define PI 3.1415926535897932384626433832795f

Renderer::Renderer(const char* name):
	mName("./Assets/Texture/"),
	mGra(0)
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
	//mName = "./Assets/Texture/";//Main.hでの描画用	
	mName = "./Assets/Texture/";
}

void Renderer::Draw(const Vector2 & pos)//画像を描画
{
	DrawGraph(pos.x - Camera2d::CameraPos.x, pos.y - Camera2d::CameraPos.y, mGra, TRUE);
}

void Renderer::Draw(int x, int y)//画像を描画
{
	DrawGraph(x - Camera2d::CameraPos.x, y - Camera2d::CameraPos.y, mGra, TRUE);
}

void Renderer::Drawb(int x, int y)//画像を描画(UIに使用)
{
	DrawGraph(x, y, mGra, TRUE);
}

void Renderer::DrawE(const Vector2 & pos, int e)//画像を描画(サイズ指定)
{
	//DrawGraph(pos.x - Camera2d::CameraPos.x, pos.y - Camera2d::CameraPos.y, mGra, TRUE);
	DrawExtendGraph(pos.x - Camera2d::CameraPos.x, pos.y - Camera2d::CameraPos.y, pos.x - Camera2d::CameraPos.x+e, pos.y - Camera2d::CameraPos.y+e, mGra, TRUE);
}

void Renderer::DrawIntegerNumber(const Vector2 & pos, int num)//Numverのみ使用できる
{
	int width = 32;
	if (num < 0)
	{
		num = 0;
	}
	int x = pos.x;
	std::string n = std::to_string(num);
	for (auto a : n)
	{
		DrawRectGraph(x, pos.y, (a - '0') * 32, 0, 32, 32, mGra, TRUE, FALSE);
		x += width;
	}
}

void Renderer::DrawNumber(const Vector2& pos, float num)//Numberのみ使用できる
{
	SetDrawBright(255, 0, 0);
	int width = 32;
	if (num < 0.f)//マイナスなら0に
	{
		num = 0.f;
	}
	int x = pos.x;
	std::string n = std::to_string(num);
	bool bbb = false;
	int count = 0;
	for (auto a : n)
	{
		if (a == '.')//.の描画
		{
			DrawRectGraph(x, pos.y, 10 * width, 0, 32, 32, mGra, TRUE, FALSE);
			bbb = true;
		}
		else//数字の描画
		{
			DrawRectGraph(x, pos.y, (a - '0')*width, 0, 32, 32, mGra, TRUE, FALSE);
			if (bbb)count++;
		}
		x += width;
		if (count >= 2)break;
	}
	SetDrawBright(255, 255, 255);
}

void Renderer::DrawBigNumber(const Vector2& pos, int num, int width)
{
	if (num < 0)
	{
		num = 0;
	}
	int x = pos.x;
	std::string n = std::to_string(num);
	for (auto a : n)
	{
		DrawRectGraph(x, pos.y, (a - '0')*width, 0, width, width, mGra, TRUE, FALSE);
		x += width;
	}
}

//描画位置、画像の開始位置、何枚目の描画か、描画範囲、反転するかどうか（TRUEなら反転）
void Renderer::DrawSerialNumber(const Vector2& pos, const Vector2& gPos, int t, const Vector2& size, bool turnFlag)
{
	
	DrawRectGraph(pos.x - Camera2d::CameraPos.x, pos.y - Camera2d::CameraPos.y, gPos.x + size.x * t, gPos.y, size.x, size.y, mGra, TRUE, turnFlag);

}

int t = 0;
bool f = FALSE;

void Renderer::DrawAlternating(int x, int y, int time)
{
	t++;
	if (t%time == 0)
	{
		f = (f) ? FALSE : TRUE;
	}
	DrawRotaGraph(x - Camera2d::CameraPos.x, y - Camera2d::CameraPos.y, 1.f, 0.f, mGra, TRUE, f);
}
