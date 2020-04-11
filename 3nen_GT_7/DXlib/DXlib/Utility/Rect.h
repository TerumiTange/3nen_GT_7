#pragma once

#include "Vector2.h"

struct Rect
{
public:
	Rect(const Vector2& pos, const Vector2& size);
	bool Intersect(const Vector2& position);
	bool Intersect(const Rect& rect);

public:
	Vector2* mPos;
	Vector2* mSize;
};