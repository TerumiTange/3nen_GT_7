
#pragma once
#include "../Device/Dx.h"
#include <list>

class Collider
{
public:
	Collider(const char* tag);
	~Collider();
	void Update();
	

private:
	int x;
	int y;
	int width;
	int height;


	std::string name;
	std::string tag;

};