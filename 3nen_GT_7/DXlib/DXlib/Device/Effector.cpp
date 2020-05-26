#include "Device\Effector.h"

Effector::Effector()
{
}

Effector::~Effector()
{
}

void Effector::Init()
{
	isElectrical = false;
}

void Effector::Lightning(Vector2 &ePos1, Vector2 &ePos2)
{
	if (isElectrical)
	{
		DrawLine(ePos1.x, ePos.y, ePos2.x, ePos.y, GetColor(255, 255, 0));
	}
}

void Effector::SetLightning(bool value)
{
	isElectrical = value;
}

void Effector::Sparkle(Vector2 &pPos)
{
}

void Effector::SetSparkle(bool value)
{
}
