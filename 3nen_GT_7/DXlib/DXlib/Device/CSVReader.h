
#pragma once
#include "DxLib.h"
#include <string>
#include <vector>
#include <string>

class CSVReader
{
public:
	CSVReader();
	CSVReader(const char* filename);
	~CSVReader();
	std::vector<int> load(const char* filename);//csvを読み込む(int型)
	std::vector<std::string> loadString(const char* filename);//csvを読み込む(文字)
	std::vector<int> getParseData() const;
	std::vector<std::string> getParseStringData() const;
	int getWidth();//横の情報量
	int getHeight();//縦の情報量

private:
	void parse(const char* filename);
	void parseString(const char* filename);

private:
	std::vector<int> mCSV;
	std::vector<std::string> mCSVString;
	int mWidthCount;
	int mHeightCount;
};