#pragma once
#include "DxLib.h"
#include <string>
#include <vector>

class CSVReader
{
public:
	CSVReader();
	CSVReader(const char* filename);
	~CSVReader();
	std::vector<int> load(const char* filename);
	std::vector<std::string> loadString(const char* filename);
	std::vector<int> getParseData() const;
	std::vector<std::string> getParseStringData() const;
	int getWidth();
	int getHeight();

private:
	void parse(const char* filename);
	void parseString(const char* filename);

private:
	std::vector<int> mCSV;
	std::vector<std::string> mCSVString;
	int mWidthCount;
	int mHeightCount;
};