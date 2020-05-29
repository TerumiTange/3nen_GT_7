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
	FLYENEMY,
	PATROLENEMY,
	RUSHENEMY
};

struct EnemyData
{
	Vector2 position;
	Vector2 PatrolPos1;
	Vector2 PatrolPos2;
	Vector2 PatrolPos3;
	Vector2 PatrolPos4;
	EnemyType type;
};

class Enemy
{
public:
	Enemy();
	~Enemy();
	void Init(const char* filename);
	void InitM(const char* filename);
	void Create(const EnemyData& data);
	void Parse(unsigned row);
	EnemyType SelectType(const std::string& name);
	size_t GetEnemyCount() const;

private:
	//CSVReader* mCSV;
	std::unique_ptr<CSVReader> mCSV;
	std::vector<std::string> mEnemyList;
	std::vector<int> mEnemyListV;
	std::list<EnemyData> mEnemyData;
	size_t mEnemyCount;
};