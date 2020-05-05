#pragma once
#include "Dx.h"
#include "../Utility/Vector2.h"

class Camera2d
{
public:
	Camera2d();
	~Camera2d();
	void Init(const Vector2& pos);
	void Update();
	void GetPPos(const Vector2& pos);
	static Vector2 CameraPos;//カメラの位置
	
private:
	Vector2* pPos;//プレーヤーの位置
};
