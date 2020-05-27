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
	
	try
	{
		std::ifstream fileOpen(filename);//ì«Ç›çûÇ›
	}
	catch (const std::exception&)
	{
		makeTxt(filename);
		return 0;
	}
	std::ifstream fileOpen(filename);//ì«Ç›çûÇ›
	std::string s;
	std::getline(fileOpen, s);
	fileOpen.close();
	return atoi(s.c_str());
}

bool Score::Write(std::string filename, int score)
{
	std::string ss;
	ss = std::to_string(score);//int Å® string
	auto aaa = Load(filename);
	if (aaa< score)
	{
		std::ofstream fileWrite(filename);//èëÇ´çûÇ›
		fileWrite << ss;
		fileWrite.close();
		return true;
	}
	return false;
}

void Score::makeTxt(std::string filename)
{
	std::ofstream fileWrite(filename);
	std::cin.get();
	Write(filename, 0);
}
