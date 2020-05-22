#include "Sound.h"


Sound::Sound():
	mSound()
{

}

Sound::~Sound()
{
	Init();
}

void Sound::Init()
{
	mSound.clear();
}

void Sound::Load(const char * filename)
{
	//mSound.emplace_back(filename, LoadSoundMem(filename));
	mSound[filename] = LoadSoundMem(filename);
}

void Sound::PlayBGM(const char * filename)
{
	if (!CheckSoundMem(mSound[filename]))
	{
		ChangeVolumeSoundMem(255 * 30 / 100, mSound[filename]);
		PlaySoundMem(mSound[filename], DX_PLAYTYPE_BACK, FALSE);
	}
}

void Sound::PlaySE(const char * filename)
{
	//if (!CheckSoundMem(mSound[filename]))
	//{
	//	PlaySoundMem(mSound[filename], DX_PLAYTYPE_BACK, FALSE);
	//}
	ChangeVolumeSoundMem(255 * 30 / 100, mSound[filename]);
	PlaySoundMem(mSound[filename], DX_PLAYTYPE_BACK, TRUE);
}

void Sound::PlaySEF(const char * filename)
{
	if (!CheckSoundMem(mSound[filename]))
	{
		ChangeVolumeSoundMem(255 * 30 / 100, mSound[filename]);
		PlaySoundMem(mSound[filename], DX_PLAYTYPE_BACK, FALSE);
	}
}

void Sound::StopBGM(const char * filename)
{
	StopSoundMem(mSound[filename]);
}
