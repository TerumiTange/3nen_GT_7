#include "Enemy.h"
#include "SmallEnemy.h"
#include "FlyEnemy.h"
#include "../Map/Map.h"

Enemy::Enemy():
	mCSV(std::make_unique<CSVReader>()),
	mEnemyList(0),
	mEnemyData(0),
	mEnemyCount(0),
	mEnemyListV(0)
{
}

Enemy::~Enemy()
{
	
}

void Enemy::Init(const char * filename)
{
	mEnemyList.clear();
	mEnemyData.clear();
	//mCSV = new CSVReader();
	mEnemyList = mCSV->loadString(filename);
	
	for (size_t i = 0; i < mCSV->getHeight(); ++i)
	{
		Parse(i);
	}
	//for (auto && b: mEnemyData)
	//{
	//	Create(b);
	//}

	auto j = mEnemyData.size();
	mEnemyCount = mEnemyData.size();
	for (int i = 0; i < j; ++i)
	{
		Create(mEnemyData.front());
		mEnemyData.pop_front();
	}
	//delete(mCSV);
}

void Enemy::InitM(const char * filename)
{
	mEnemyList.clear();
	mEnemyData.clear();
	mEnemyListV.clear();
	mEnemyListV = mCSV->load(filename);
	auto a = mEnemyListV.size();
	auto w = mCSV->getWidth();
	for (int i = mEnemyListV.size() - 1; i >= 0; --i)
	{
		EnemyData data;
		data.position = Vector2(i % mCSV->getWidth() * 32, i / mCSV->getWidth() * 32);
		switch (mEnemyListV[i])
		{
		case 0: break;
		case 1: data.type = EnemyType::FLYENEMY; mEnemyData.emplace_back(data); break;
		default:
			break;
		}
		
	}
	auto j = mEnemyData.size();
	mEnemyCount = mEnemyData.size();
	for (int i = 0; i < j; ++i)
	{
		Create(mEnemyData.front());
		mEnemyData.pop_front();
	}
	//delete(mEnemyData);
}

void Enemy::Create(const EnemyData& data)
{
	if (data.type == EnemyType::SMALLENEMY)
	{
		auto e = new SmallEnemy(data.position);
	}

	if (data.type == EnemyType::FLYENEMY)
	{
		auto e = new FlyEnemy(data.position);
	}
}

void Enemy::Parse(unsigned row)
{
	EnemyData data;
	const int num = mCSV->getWidth()*row;
	data.type = SelectType(mEnemyList.at(num+1));
	data.position.x = atoi(mEnemyList.at(num + 2).c_str());//3çsñ⁄
	data.position.y = Map::height * 32 - atoi(mEnemyList.at(num + 3).c_str());//4çsñ⁄

	mEnemyData.emplace_back(data);
}

EnemyType Enemy::SelectType(const std::string & name)
{
	if (name == "SmallEnemy")
	{
		return EnemyType::SMALLENEMY;
	}

	if (name == "FlyEnemy")
	{
		return EnemyType::FLYENEMY;
	}

	return EnemyType::SMALLENEMY;
}

size_t Enemy::GetEnemyCount() const
{
	return mEnemyCount;
}
