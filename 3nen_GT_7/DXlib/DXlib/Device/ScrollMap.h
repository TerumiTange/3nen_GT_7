#pragma once

#include "Dx.h"
#include"../Utility/Vector2.h"

class ScrollMap {
public:
	ScrollMap(const Vector2 &mapSize);
	~ScrollMap();

	void Init();
	void Update(const Vector2 & plPos,const int & mapWidth,const int & mapHwight);
	void CalScroll(const Vector2 &plPos);
	int ScrollX();
	int ScrollY();

private:
	Vector2* mPlPos;
	Vector2* mMapSize;
	Vector2 mScroll;

};