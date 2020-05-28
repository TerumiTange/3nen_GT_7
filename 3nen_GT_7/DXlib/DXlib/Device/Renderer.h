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
	//�摜��`��(int�w��)
	void Draw(int x, int y);
	//�摜��`��(UI�Ɏg�p)
	void Drawb(int x, int y);
	//�摜��`��(�T�C�Y�w��)
	void DrawE(const Vector2& pos, int e);
	//������p
	void DrawIntegerNumber(const Vector2& pos, int num);
	//������p
	void DrawNumber(const Vector2& pos, float num);
	//�A��
	void DrawSerialNumber(const Vector2& pos, const Vector2& gPos, int t, const Vector2& size, bool turnFlag);
private:
	std::string mName;
	int mGra;

	int width;
};