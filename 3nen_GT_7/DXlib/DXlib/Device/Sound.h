#pragma once

#include "Dx.h"
#include <map>

class Sound
{
public:
	Sound();
	~Sound();
	void Init();
	void Load(const char* filename);
	void PlayBGM(const char* filename);
	void PlaySE(const char* filename);
	void PlaySEF(const char* filename);
	void StopBGM(const char* filename);
	void DeleteM(const char* filename);
private:
	std::map<const char*, int> mSound;
};
