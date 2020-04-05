#include "Map.h"

Map::Map():
	mCSVReader(nullptr),
	mCSV(0),
	mGimmickData(0),
	mWall(0)
{

}

Map::~Map()
{
}

void Map::Init(const char* filename)
{
	mCSV.clear();
	mGimmickData.clear();
	mWall.clear();
	mCSVReader = new CSVReader(filename);
	mCSV = mCSVReader->load(filename);

	width = mCSVReader->getWidth();
	height = mCSVReader->getHeight();

	auto a = mCSV.size();
	for (int i = mCSV.size() - 1; i >= 0; --i)
	{
		GimmickData data;
		data.position = Vector2(i % mCSVReader->getWidth() * 32, i / mCSVReader->getWidth() * 32);
		switch (mCSV[i])
		{
		case 0:data.type = Category::EMPTY; break;
		case 1:data.type = Category::WALL; break;
		case 2:data.type = Category::FLOOR; break;
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

void Map::Update()
{
	//for (int i = 0; i < mWall.size(); ++i)
	//{
	//	mWall[i]->Update();
	//}
}

void Map::Draw()
{
	for (auto&& itr : mWall)
	{
		itr->Draw();
	}
	//for (int i = 0; i < mWall.size(); ++i)
	//{
	//	mWall[i].Draw();
	//	
	//}

	//std::list<std::shared_ptr<Wall>>::iterator itr;
	//for (itr = mWall.begin(); itr != mWall.end(); ++itr)
	//{
	//	itr->Draw();
	//}

}

void Map::Create(const GimmickData & data)
{
	if (data.type == Category::WALL)
	{
		//auto w = new Wall(data.position);
		//mWall.emplace_back(new Wall(data.position));
		mWall.emplace_back(new Wall(data.position));
	}
	else if(data.type == Category::FLOOR)
	{

	}
}

int Map::width = 0;
int Map::height = 0;