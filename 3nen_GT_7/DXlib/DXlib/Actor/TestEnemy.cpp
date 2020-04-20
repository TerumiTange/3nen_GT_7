#include "TestEnemy.h"
#include "../Utility/Vector2.h"
#include "DxLib.h"

TestEnemy::TestEnemy(const Vector2& position, const char* tag) :
	Actor(tag),
	mPos(new Vector2()),
	mFilename(tag),
	mFall(true)
{
	*mPos = position;
	Actor::SetPos(*mPos);
	Actor::SetSize(*new Vector2(32, 32));
}

TestEnemy::~TestEnemy() = default;

void TestEnemy::Init()
{

}

void TestEnemy::Update()
{

}

void TestEnemy::Draw()
{
	//renderer.Draw(filename, *pos);
	//test—p
	int a;
	a = LoadGraph("./Assets/Texture/Enemy.png");
	DrawGraph(mPos->x, mPos->y, a, TRUE);
	DeleteGraph(a);
}

void TestEnemy::Hit()
{

}
