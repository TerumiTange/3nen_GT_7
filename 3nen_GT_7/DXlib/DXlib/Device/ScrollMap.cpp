#include"ScrollMap.h"
#include"WindowSize.h"

ScrollMap::ScrollMap(const Vector2 & mapSize):mPlPos(new Vector2()),mMapSize(new Vector2())
{}

ScrollMap::~ScrollMap()
{}

//初期化
void ScrollMap::Init()
{
	mScroll = Vector2(0, 0);
}

//更新
void ScrollMap::Update(const Vector2 & plPos,const int & mapWidth,const int & mapHeight)
{
	CalScroll(plPos);
}

//動き幅の計算//ここがうまくできない。エラーが大量だからすべて消しとく
void ScrollMap::CalScroll(const Vector2 & plPos)
{

}

//X値を返す・・ここをマップに足す感じ
int ScrollMap::ScrollX()
{
	return mScroll.x;
}

//Y値を返す・・ここをマップに足す感じ
int ScrollMap::ScrollY()
{
	return mScroll.y;
}
