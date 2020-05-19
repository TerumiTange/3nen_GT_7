#pragma once

#include "../Utility/Vector2.h"

//�l�p�`
struct Quadrangle
{
	Quadrangle(const Vector2& pos, const Vector2& s);
	void set(const Vector2& pos, const Vector2& s);
	
	Vector2 position;
	Vector2 size;
};

//�������Ă��邩�ǂ���
bool CheckHit(const Quadrangle& a, const Quadrangle& b);