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
	//�摜��`��(UI�Ɏg�p)(�J�����Ɉˑ����Ȃ�)
	void Drawb(int x, int y);
	//�摜��`��(�T�C�Y�w��)
	void DrawE(const Vector2& pos, int e);
	//������p
	void DrawIntegerNumber(const Vector2& pos, int num);
	//Number��p
	void DrawNumber(const Vector2& pos, float num);
	//�g�[�^���X�R�A�p
	void DrawBigNumber(const Vector2& pos, int num, int width);
	//�A��
	void DrawSerialNumber(const Vector2& pos, const Vector2& gPos, int t, const Vector2& size, bool turnFlag);
	//����
	void DrawAlternating(int x, int y, int time);

private:
	std::string mName;
	int mGra;

};