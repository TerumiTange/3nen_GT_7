#pragma once
#include "Dx.h"
#include "../Utility/Vector2.h"

#include <map>

class Renderer
{
public:
	//コンストラクタ
	Renderer();
	//デストラクタ
	~Renderer();
	//初期化
	void Init();
	//画像読み込み
	void LoadTexture(const char* filename);
	//画像を描画
	void Draw(const char* filename, Vector2& position);
	void Draw(const char* filename, int x, int y);
private:
	std::map<const char*, int>texture;
	std::string name;
};