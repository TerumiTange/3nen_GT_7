#pragma once
#include "../Device/Dx.h"
#include "../Device/CSVReader.h"
#include "../Utility/Vector2.h"
#include <string>
#include <list>
#include <vector>

enum class EnemyType
{
	SMALLENEMY,
};

struct EnemyData
{
	Vector2 position;
	EnemyType type;
};

class Enemy
{
public:
	Enemy();
	~Enemy();
	void Init(const char* filename);
	void Create(const EnemyData& data);
	void Parse(unsigned row);
	EnemyType SelectType(const std::string& name);

private:
	//CSVReader* mCSV;
	std::unique_ptr<CSVReader> mCSV;
	std::vector<std::string> mEnemyList;
	std::list<EnemyData> mEnemyData;
};