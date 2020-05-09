#pragma once
#include "../Device/Dx.h"
#include "../Device/CSVReader.h"
#include "../Utility/Vector2.h"
#include <list>
#include <vector>

enum class Category
{
	EMPTY,//空白
	WALL, //壁
	FLOOR,//床
	METAL,//金属
	GOAL,//ゴール
	DEATH,//デスブロック
};

struct GimmickData
{
	Vector2 position;
	Category type;
};

class Map
{
public:
	Map();
	~Map();
	void Init(const char* file);
	int ReturnWidth();//マップ全体の横大きさ
	int ReturnHeight();//マップ全体の縦大きさ
	void Create(const GimmickData& data);

	static int width;
	static int height;
	static int size;

private:
	CSVReader* mCSVReader;
	std::vector<int> mCSV;
	std::list<GimmickData> mGimmickData;
	std::string mFilename;
	//std::list<Wall> mWall;
	//std::list<std::shared_ptr<Wall>> mWall;
};