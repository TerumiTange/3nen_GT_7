
#include "Collider.h"

Collider::Collider(const char* tag):
	x(0),
	y(0),
	width(0),
	height(0),
	name(""),
	tag(tag)
{
	name = "../Assets/Texture/";
	name = name + tag + ".png";
	int GHandle = LoadGraph(name.c_str());
	GetGraphSize(GHandle, &width, &height);
	DeleteGraph(GHandle);
}

Collider::~Collider()
{
	delete(&name);
}

void Collider::Update()
{

}
