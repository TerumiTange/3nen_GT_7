#pragma once

#include "Vector2.h"

enum Range
{
	Top,    //è„
	Buttom, //â∫
	Right,	//âE
	Left,	//ç∂
	Non	//
};

struct Rect
{
public:
	Rect(const Vector2& pos, const Vector2& size);
	~Rect();
	void Init();
	bool Intersect(const Vector2& position);
	bool Intersect(const Rect& rect);
	Range& Point();
	void SetPos(Vector2& pos);
public:
	Vector2* mPos;
	Vector2* mSize;
	Range* mRange;
};