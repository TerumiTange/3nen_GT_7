#include"ScrollMap.h"
#include"WindowSize.h"

ScrollMap::ScrollMap(const Vector2 & mapSize):mPlPos(new Vector2()),mMapSize(new Vector2())
{}

ScrollMap::~ScrollMap()
{}

//������
void ScrollMap::Init()
{
	mScroll = Vector2(0, 0);
}

//�X�V
void ScrollMap::Update(const Vector2 & plPos,const int & mapWidth,const int & mapHeight)
{
	CalScroll(plPos);
}

//�������̌v�Z//���������܂��ł��Ȃ��B�G���[����ʂ����炷�ׂď����Ƃ�
void ScrollMap::CalScroll(const Vector2 & plPos)
{

}

//X�l��Ԃ��E�E�������}�b�v�ɑ�������
int ScrollMap::ScrollX()
{
	return mScroll.x;
}

//Y�l��Ԃ��E�E�������}�b�v�ɑ�������
int ScrollMap::ScrollY()
{
	return mScroll.y;
}
