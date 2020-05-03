
#include "Renderer.h"


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

void Renderer::Draw(const Vector2 & pos)
{
	DrawGraph(pos.x, pos.y, mGra, TRUE);
}

void Renderer::Draw(int x, int y)
{
	DrawGraph(x, y, mGra, TRUE);
}
