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
	std::vector<int> load(const char* filename);//csv‚ğ“Ç‚İ‚Ş(intŒ^)
	std::vector<std::string> loadString(const char* filename);//csv‚ğ“Ç‚İ‚Ş(•¶š)
	std::vector<int> getParseData() const;
	std::vector<std::string> getParseStringData() const;
	int getWidth();//‰¡‚Ìî•ñ—Ê
	int getHeight();//c‚Ìî•ñ—Ê

private:
	void parse(const char* filename);
	void DxParse(const char* filename);
	void parseString(const char* filename);

private:
	std::vector<int> mCSV;
	std::vector<std::string> mCSVString;
	int mWidthCount;
	int mHeightCount;
};