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
	CameraPos.y = pPos->y - ((ScreenHeight / 3) * 2);
	//position = VGet(pPos->x, pPos->y, 0);
	// �J�����̐ݒ�ɔ��f����
	//SetCameraPositionAndTarget_UpVecY(position, VGet(0, 0, 0));
	if (CameraPos.x < 0)//�J�����̈ʒuX��0�ȉ��ɂȂ�����0�ɂ���
	{
		CameraPos.x = 0;
	}
	if (CameraPos.x > (Map::width) * 32 - ScreenWidth)//�J�����̈ʒu���X�e�[�W�[���ڂ������ɂȂ�����
	{
		CameraPos.x = (Map::width) * 32 - ScreenWidth;
	}
	if (CameraPos.y < 0)
	{
		CameraPos.y = 0;
	}
	if (CameraPos.y > (Map::height) * 32 - ScreenHeight)
	{
		CameraPos.y = (Map::height) * 32 - ScreenHeight;
	}
}

void Camera2d::GetPPos(const Vector2& pos)
{
	*pPos = pos;//�v���[���[�̈ʒu

}

Vector2 Camera2d::CameraPos = Vector2(0,0);