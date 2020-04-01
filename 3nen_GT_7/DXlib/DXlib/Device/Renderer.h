#pragma once
#include "Dx.h"
#include "../Utility/Vector2.h"

#include <map>

class Renderer
{
public:
	//�R���X�g���N�^
	Renderer();
	//�f�X�g���N�^
	~Renderer();
	//������
	void Init();
	//�摜�ǂݍ���
	void LoadTexture(const char* filename);
	//�摜��`��
	void Draw(const char* filename, Vector2& position);
	void Draw(const char* filename, int x, int y);
private:
	std::map<const char*, int>texture;
	std::string name;
};