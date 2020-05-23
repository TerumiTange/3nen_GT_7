#include "Score.h"

#include <iostream>
#include <fstream>

Score::Score()
{
}

Score::~Score()
{
}

int Score::Load(std::string filename)
{
	std::ifstream fileOpen(filename);//読み込み
	std::string s;
	std::getline(fileOpen, s);
	fileOpen.close();
	return atoi(s.c_str());
}

bool Score::Write(std::string filename, int score)
{
	std::string ss;
	ss = std::to_string(score);//int → string

	if (Load(filename) < score)
	{
		std::ofstream fileWrite(filename);//書き込み
		fileWrite << ss;
		fileWrite.close();
		return true;
	}
	return false;
}
