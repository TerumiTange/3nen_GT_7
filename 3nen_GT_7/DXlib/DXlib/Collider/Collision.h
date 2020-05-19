#pragma once

#include "../Utility/Vector2.h"

//四角形
struct Quadrangle
{
	Quadrangle(const Vector2& pos, const Vector2& s);
	void set(const Vector2& pos, const Vector2& s);
	
	Vector2 position;
	Vector2 size;
};

//あたっているかどうか
bool CheckHit(const Quadrangle& a, const Quadrangle& b);