#pragma once
#include "../Device/Dx.h"
#include "../Device/CSVReader.h"

enum Type
{
	BLANK,//��
	FLOOR,//��

};
class Map
{
public:
	Map();
private:
	CSVReader* mCSVReader;
};