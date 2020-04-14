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
		if (!(mPos->y + mSize->y <= rect.mPos->y))//�����̉��ɓ������Ă��Ȃ����
		{
			*mRange = Range::Top;//��ɓ������Ă���
		}
		else if (!(mPos->y > rect.mPos->y + rect.mPos->y))//�����̏�ɓ������Ă��Ȃ����
		{
			*mRange = Range::Buttom;//���ɓ������Ă���
		}
		else if (!(mPos->x + mSize->x <= rect.mPos->x))//�����̉E���ɓ������Ă��Ȃ����
		{
			*mRange = Range::Left;//���ɓ������Ă���
		}
		else if (!(mPos->x > rect.mPos->x + rect.mSize->x))//�����̍����ɓ������Ă��Ȃ����
		{
			*mRange = Range::Right;//�E�ɓ������Ă���
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
