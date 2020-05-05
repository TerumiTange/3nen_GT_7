#include "Camera2d.h"
#include "../Map/Map.h"
#include "WindowSize.h"

Camera2d::Camera2d():
	pPos(new Vector2(0,0))
{
	
}

Camera2d::~Camera2d()
{
	delete(pPos);
}

void Camera2d::Init(const Vector2& pos)
{
	CameraPos = pos;
}

void Camera2d::Update()
{

	CameraPos.x = pPos->x - (ScreenWidth / 2);
	//position = VGet(pPos->x, pPos->y, 0);
	// カメラの設定に反映する
	//SetCameraPositionAndTarget_UpVecY(position, VGet(0, 0, 0));
	if (CameraPos.x < 0)//カメラの位置Xが0以下になったら0にする
	{
		CameraPos.x = 0;
	}
	if (CameraPos.x > (Map::width) * 32 - ScreenWidth)//カメラの位置がステージ端を移しそうになったら
	{
		CameraPos.x = (Map::width) * 32 - ScreenWidth;
	}
}

void Camera2d::GetPPos(const Vector2& pos)
{
	*pPos = pos;//プレーヤーの位置

}

Vector2 Camera2d::CameraPos = Vector2(0,0);