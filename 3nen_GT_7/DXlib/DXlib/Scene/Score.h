#pragma once
#include <string>

class Score
{
public:
	Score();
	~Score();
	int Load(std::string filename);
	bool Write(std::string filename, int score);
	void makeTxt(std::string filename);
};