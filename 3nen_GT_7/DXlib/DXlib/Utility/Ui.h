#pragma once

#include "Vector2.h"
#include "DxLib.h"

class UI
{
public:
	UI();
	UI(const Vector2 &position,const Vector2 &size,const int &maxVolum, int texture);
	~UI();

	void Init();
	void Active(bool set);
	void Gauge(int volum,int maxVolum);
	void Cell(int volum, int maxVolum);

private:
	Vector2* mPos;
	Vector2* mSize;
	int mTexture;
	int mVolum;
	int mMaxVolum;
	bool active;
};