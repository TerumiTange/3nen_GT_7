#pragma once
#include "Dx.h"
#include "../Utility/Vector2.h"

#include <map>

class Renderer
{
public:
	//コンストラクタ
	Renderer(const char* name);
	//デストラクタ
	~Renderer();
	//初期化
	void Init();
	//画像を描画
	void Draw(const Vector2& pos);
	void Draw(int x, int y);
	void Drawb(int x, int y);
	void DrawE(const Vector2& pos, int e);
	void DrawIntegerNumber(const Vector2& pos, int num);//整数専用
	void DrawNumber(const Vector2& pos, float num);
	void DrawSerialNumber(const Vector2& pos, const Vector2& gPos, int t, const Vector2& size, bool turnFlag);//連番
private:
	std::string mName;
	int mGra;

	int width;
};