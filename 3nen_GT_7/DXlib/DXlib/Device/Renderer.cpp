
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
	//mName = "./Assets/Texture/";//Main.h‚Å‚Ì•`‰æ—p	
	mName = "./Assets/Texture/";
}

void Renderer::Draw(const Vector2 & pos)//‰æ‘œ‚ð•`‰æ
{
	DrawGraph(pos.x - Camera2d::CameraPos.x, pos.y - Camera2d::CameraPos.y, mGra, TRUE);
}

void Renderer::Draw(int x, int y)//‰æ‘œ‚ð•`‰æ
{
	DrawGraph(x - Camera2d::CameraPos.x, y - Camera2d::CameraPos.y, mGra, TRUE);
}

void Renderer::Drawb(int x, int y)//‰æ‘œ‚ð•`‰æ(UI‚ÉŽg—p)
{
	DrawGraph(x, y, mGra, TRUE);
}

void Renderer::DrawE(const Vector2 & pos, int e)//‰æ‘œ‚ð•`‰æ(ƒTƒCƒYŽw’è)
{
	//DrawGraph(pos.x - Camera2d::CameraPos.x, pos.y - Camera2d::CameraPos.y, mGra, TRUE);
	DrawExtendGraph(pos.x - Camera2d::CameraPos.x, pos.y - Camera2d::CameraPos.y, pos.x - Camera2d::CameraPos.x+e, pos.y - Camera2d::CameraPos.y+e, mGra, TRUE);
}

void Renderer::DrawIntegerNumber(const Vector2 & pos, int num)//Numver‚Ì‚ÝŽg—p‚Å‚«‚é
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

void Renderer::DrawNumber(const Vector2& pos, float num)//Number‚Ì‚ÝŽg—p‚Å‚«‚é
{
	SetDrawBright(255, 0, 0);
	int width = 32;
	if (num < 0.f)//ƒ}ƒCƒiƒX‚È‚ç0‚É
	{
		num = 0.f;
	}
	int x = pos.x;
	std::string n = std::to_string(num);
	bool bbb = false;
	int count = 0;
	for (auto a : n)
	{
		if (a == '.')//.‚Ì•`‰æ
		{
			DrawRectGraph(x, pos.y, 10 * width, 0, 32, 32, mGra, TRUE, FALSE);
			bbb = true;
		}
		else//”Žš‚Ì•`‰æ
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

//•`‰æˆÊ’uA‰æ‘œ‚ÌŠJŽnˆÊ’uA‰½–‡–Ú‚Ì•`‰æ‚©A•`‰æ”ÍˆÍA”½“]‚·‚é‚©‚Ç‚¤‚©iTRUE‚È‚ç”½“]j
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
