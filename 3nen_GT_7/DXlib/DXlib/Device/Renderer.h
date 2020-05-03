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
private:
	std::string mName;
	int mGra;
};