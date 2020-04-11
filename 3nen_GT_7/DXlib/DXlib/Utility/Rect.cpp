#include "Rect.h"

Rect::Rect(const Vector2 & pos, const Vector2 & size):
	mPos(),
	mSize()
{
	*mPos = pos;
	*mSize = size;
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
		return true;
	}
	return false;
}
