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
	//画像を描画(int指定)
	void Draw(int x, int y);
	//画像を描画(UIに使用)
	void Drawb(int x, int y);
	//画像を描画(サイズ指定)
	void DrawE(const Vector2& pos, int e);
	//整数専用
	void DrawIntegerNumber(const Vector2& pos, int num);
	//整数専用
	void DrawNumber(const Vector2& pos, float num);
	//連番
	void DrawSerialNumber(const Vector2& pos, const Vector2& gPos, int t, const Vector2& size, bool turnFlag);
private:
	std::string mName;
	int mGra;

	int width;
};