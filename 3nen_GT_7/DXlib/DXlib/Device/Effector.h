#pragma once
#include "Dx.h"
#include "../Utility/Vector2.h"
#include "Renderer.h"

class Effector
{
public:
	Effector();
	~Effector();

	void Init();
	void Lightning(Vector2 ePos1,Vector2 ePos2);
	void SetLightning(bool value);
	void Sparkle(Vector2 pPos);
	void SetSparkle(bool value);

private:
	int litGraph;          //電気の鎖用画像
	int sparkGraph;        //火花用
	bool isElectrical;     //オンオフ
	bool isSparkle;        //オンオフ

	//計算値保存用
	Vector2 ePos;          
	double radian;

};