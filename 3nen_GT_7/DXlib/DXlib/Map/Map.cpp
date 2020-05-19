#include "Map.h"
#include "../Actor/Wall.h"
#include "../Actor/Floor.h"
#include "../Actor/Player.h"

Map::Map():
	mCSVReader(nullptr),
	mCSV(0),
	mGimmickData(0),
	mFilename("./Assets/Data/")
	//mWall(0)
{

}

Map::~Map()
{
}

void Map::Init(const char* file)
{
	mFilename = mFilename + file + ".csv";
	mCSV.clear();
	mGimmickData.clear();
	mCSVReader = new CSVReader(mFilename.c_str());
	mCSV = mCSVReader->load(mFilename.c_str());

	width = mCSVReader->getWidth();
	height = mCSVReader->getHeight();

	auto a = mCSV.size();
	for (int i = mCSV.size() - 1; i >= 0; --i)
	{
		GimmickData data;
		data.position = Vector2(i % mCSVReader->getWidth() * 32, i / mCSVReader->getWidth() * 32);
		switch (mCSV[i])
		{
		case 0:data.type = Category::EMPTY; break;//空白
		case 1:data.type = Category::WALL; break; //壁
		case 2:data.type = Category::FLOOR; break;//床
		case 8:data.type = Category::PLAYER; break;//プレイヤー
		case 99:data.type = Category::EMPTY; break;//例外処理用
		default:
			break;
		}
		mGimmickData.emplace_back(data);
	}
	auto j = mGimmickData.size();
	for (int i = 0; i < j; ++i)
	{
		Create(mGimmickData.front());
		mGimmickData.pop_front();
	}
	delete(mCSVReader);//
}

int Map::ReturnWidth()
{
	return width * 32;
}

int Map::ReturnHeight()
{
	return height * 32;
}


void Map::Create(const GimmickData & data)
{
	if (data.type == Category::WALL)
	{
		auto w = new Wall(data.position);
		//mWall.emplace_back(new Wall(data.position));
		//mWall.emplace_back(new Wall(data.position));
	}
	else if(data.type == Category::FLOOR)
	{
		auto f = new Floor(data.position);
	}
	else if (data.type == Category::PLAYER)
	{
		auto p = new Player(data.position);
	}
}

int Map::width = 0;
int Map::height = 0;