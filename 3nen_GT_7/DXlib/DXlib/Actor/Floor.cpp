#include "Floor.h"

Floor::Floor(const Vector2& position, const char* tag) :
	Actor(tag),
	mPos(new Vector2()),
	mFilename(tag),
	mRenderer(new Renderer())
{
	*mPos = position;
	Actor::SetPos(*mPos);
	Actor::SetSize(*new Vector2(32, 32));
}

Floor::~Floor() = default;

void Floor::Update()
{

}

void Floor::Draw()
{
	int a;
	a = LoadGraph("./Assets/Texture/Floor.png");
	DrawGraph(mPos->x, mPos->y, a, TRUE);
	DeleteGraph(a);
}

void Floor::Hit()
{
}
