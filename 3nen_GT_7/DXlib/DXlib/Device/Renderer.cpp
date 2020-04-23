
#include "Renderer.h"


#define PI 3.1415926535897932384626433832795f


Renderer::Renderer():
	texture(),
	name("../Assets/Texture/")
{
	
}

Renderer::~Renderer()
{
}

void Renderer::Init()
{
	//name = "./Assets/Texture/";//Main.h‚Å‚Ì•`‰æ—p	
	name = "./Assets/Texture/";
}

void Renderer::LoadTexture(const char* filename)
{
	//assets = name + *filename;
	//assets = strcat(name, filename);
	Init();
	name = name + filename + ".png";
	texture[name.c_str()] = LoadGraph(name.c_str());
	Init();
}


void Renderer::Draw(const char* filename, Vector2& position)
{
	Init();
	name = name + filename + ".png";
	//printfDx("‰æ‘œ–¼%s",name.c_str());
	//DrawGraph(position.x, position.y, texture[name.c_str()], TRUE);
	int mGra = LoadGraph(name.c_str());
	DrawGraph(position.x, position.y, mGra, TRUE);
	DeleteGraph(mGra);
	Init();
}

void Renderer::Draw(const char* filename, int x, int y)
{
	Init();
	name = name + filename + ".png";
	//DrawGraph(x, y, texture[name.c_str()], TRUE);
	int mGra = LoadGraph(name.c_str());
	DrawGraph(x, y, mGra, TRUE);
	DeleteGraph(mGra);
	Init();
}
