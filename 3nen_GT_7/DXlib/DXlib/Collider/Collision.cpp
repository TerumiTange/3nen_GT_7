#include "Collision.h"
#include <algorithm>
#include <array>
#include <vector>

Quadrangle::Quadrangle(const Vector2 & pos, const Vector2 & s):
	position(pos),
	size(s)
{
}

void Quadrangle::set(const Vector2 & pos, const Vector2 & s)
{
	this->position = pos;
	this->size = s;
}

bool CheckHit(const Quadrangle & a, const Quadrangle & b)
{
	int L1 = a.position.x;
	int R1 = a.position.x + a.size.x;
	int L2 = b.position.x;
	int R2 = b.position.x + b.size.x;
	if (R1 < L2)return false;
	if (R2 < L1)return false;

	int U1 = a.position.y;
	int D1 = a.position.y + a.size.y;
	int U2 = b.position.y;
	int D2 = b.position.y + b.size.y;
	if (D1 < U2)return false;
	if (D2 < U1)return false;

	return true;
}

bool CheckHit(int x, int y, int width, int height, int x2, int y2, int width2, int height2)
{
	if (x + width < x2)return false;
	if (x2 + width2 < x)return false;
	if (y + height < y2)return false;
	if (y2 + height2 < y)return false;
	return true;
}
