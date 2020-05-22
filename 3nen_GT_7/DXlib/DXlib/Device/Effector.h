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
	int litGraph;          //�d�C�̍��p�摜
	int sparkGraph;        //�Ήԗp
	bool isElectrical;     //�I���I�t
	bool isSparkle;        //�I���I�t

	//�v�Z�l�ۑ��p
	Vector2 ePos;          
	double radian;

};