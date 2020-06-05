#include "Enemy.h"
#include "FlyEnemy.h"
#include "PatrolEnemy.h"
#include "RushEnemy.h"
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
	mEnemyCount += mEnemyData.size();
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
		case 2: data.type = EnemyType::PATROLENEMY; mEnemyData.emplace_back(data); break;
		case 3: data.type = EnemyType::RUSHENEMY; mEnemyData.emplace_back(data); break;
		default:
			break;
		}
		
	}
	auto j = mEnemyData.size();
	mEnemyCount += mEnemyData.size();
	for (int i = 0; i < j; ++i)
	{
		Create(mEnemyData.front());
		mEnemyData.pop_front();
	}
	//delete(mEnemyData);
}

void Enemy::Create(const EnemyData& data)
{

	if (data.type == EnemyType::FLYENEMY)
	{
		auto e = new FlyEnemy(data.position);
	}

	if (data.type == EnemyType::PATROLENEMY)
	{
		auto e = new PatrolEnemy(data.position, data.PatrolPos1, data.PatrolPos2, data.PatrolPos3, data.PatrolPos4);
	}

	if (data.type == EnemyType::RUSHENEMY)
	{
		auto e = new RushEnemy(data.position);
	}
}

void Enemy::Parse(unsigned row)
{
	EnemyData data;
	const int num = mCSV->getWidth()*row;
	data.type = SelectType(mEnemyList.at(num+1));
	//出現位置かつ追跡後に戻る位置
	data.position.x = atoi(mEnemyList.at(num + 2).c_str());//3行目
	data.position.y = Map::height * 32 - atoi(mEnemyList.at(num + 3).c_str());//4行目
	//巡回位置1
	data.PatrolPos1.x = atoi(mEnemyList.at(num + 4).c_str());//5行目
	data.PatrolPos1.y = Map::height * 32 - atoi(mEnemyList.at(num + 5).c_str());//6行目
	//巡回位置2
	data.PatrolPos2.x = atoi(mEnemyList.at(num + 6).c_str());//7行目
	data.PatrolPos2.y = Map::height * 32 - atoi(mEnemyList.at(num + 7).c_str());//8行目
	//巡回位置3
	data.PatrolPos3.x = atoi(mEnemyList.at(num + 8).c_str());//9行目
	data.PatrolPos3.y = Map::height * 32 - atoi(mEnemyList.at(num +9).c_str());//10行目
	//巡回位置4
	data.PatrolPos4.x = atoi(mEnemyList.at(num + 10).c_str());//11行目
	data.PatrolPos4.y = Map::height * 32 - atoi(mEnemyList.at(num + 11).c_str());//12行目

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

	if (name == "PatrolEnemy")
	{
		return EnemyType::PATROLENEMY;
	}

	if (name == "RushEnemy")
	{
		return EnemyType::RUSHENEMY;
	}

	return EnemyType::SMALLENEMY;
}

size_t Enemy::GetEnemyCount() const
{
	return mEnemyCount;
}
