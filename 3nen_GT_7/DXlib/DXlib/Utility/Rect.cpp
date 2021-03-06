#include "Rect.h"
#include <memory>

Rect::Rect(const Vector2& pos, const Vector2 & size):
	mPos(new Vector2()),
	mSize(new Vector2()),
	mRange(new Range())
{
	*mPos = pos;
	*mSize = size;
	Init();
}

Rect::~Rect()
{
}

void Rect::Init()
{
	*mRange = Range::Non;
}

bool Rect::Intersect(const Vector2 & position)
{
	if (
		(position.x >= mPos->x) &&
		(position.x < mPos->x + mSize->x) &&
		(position.y >= mPos->y) &&
		(position.y < mPos->y + mSize->y)
		)
	{
		return true;
	}
	return false;
}

bool Rect::Intersect(const Rect & rect)
{
	if (
		(mPos->x + mSize->x >= rect.mPos->x) &&
		(mPos->x < rect.mPos->x + rect.mSize->x) &&
		(mPos->y + mSize->y >= rect.mPos->y) &&
		(mPos->y < rect.mPos->y + rect.mPos->y)
		)
	{
		if (!(mPos->y + mSize->y <= rect.mPos->y))//自分の下に当たっていなければ
		{
			*mRange = Range::Top;//上に当たっている
		}
		else if (!(mPos->y > rect.mPos->y + rect.mPos->y))//自分の上に当たっていなければ
		{
			*mRange = Range::Buttom;//下に当たっている
		}
		else if (!(mPos->x + mSize->x <= rect.mPos->x))//自分の右側に当たっていなければ
		{
			*mRange = Range::Left;//左に当たっている
		}
		else if (!(mPos->x > rect.mPos->x + rect.mSize->x))//自分の左側に当たっていなければ
		{
			*mRange = Range::Right;//右に当たっている
		}


		return true;
	}

	return false;
}

Range & Rect::Point()
{
	return *mRange;
}

void Rect::SetPos(Vector2 & pos)
{
	mPos = &pos;
}
