#pragma once
#include "../Device/Dx.h"
#include "../Device/CSVReader.h"
#include "../Utility/Vector2.h"
#include "../Actor/Wall.h"
#include <list>

enum class Category
{
	EMPTY,//��
	WALL, //��
	FLOOR,//��
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
	void Init(const char* filename);
	int ReturnWidth();//�}�b�v�S�̂̉��傫��
	int ReturnHeight();//�}�b�v�S�̂̏c�傫��
	void Update();
	void Draw();
	void Create(const GimmickData& data);

	static int width;
	static int height;
	static int size;

private:
	CSVReader* mCSVReader;
	std::vector<int> mCSV;
	std::list<GimmickData> mGimmickData;
	std::vector<Wall>mWall;
};