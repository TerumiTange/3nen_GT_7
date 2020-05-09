#pragma once
#include "../Device/Dx.h"
#include "../Device/CSVReader.h"
#include "../Utility/Vector2.h"
#include <list>
#include <vector>

enum class Category
{
	EMPTY,//��
	WALL, //��
	FLOOR,//��
	METAL,//����
	GOAL,//�S�[��
	DEATH,//�f�X�u���b�N
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
	int ReturnWidth();//�}�b�v�S�̂̉��傫��
	int ReturnHeight();//�}�b�v�S�̂̏c�傫��
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