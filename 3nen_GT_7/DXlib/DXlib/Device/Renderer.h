#pragma once
#include "Dx.h"
#include "../Utility/Vector2.h"

#include <map>

class Renderer
{
public:
	//�R���X�g���N�^
	Renderer(const char* name);
	//�f�X�g���N�^
	~Renderer();
	//������
	void Init();
	//�摜��`��
	void Draw(const Vector2& pos);
private:
	std::string mName;
	int mGra;
};