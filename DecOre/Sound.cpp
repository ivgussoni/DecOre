#include "Sound.h"

SDL::Sound::Sound(std::string filePath)
{
	SetPath(filePath);
}

SDL::Sound::~Sound()
{
	Mix_FreeChunk(_sound);
	_sound = nullptr;
}

void SDL::Sound::SetPath(std::string filePath)
{
	_sound = Mix_LoadWAV(filePath.c_str());
}

void SDL::Sound::Play(float volume, bool repeat)
{
	Mix_VolumeChunk(_sound, int(128 * volume));

	if (_sound != NULL)
	{
		Mix_FadeInChannel(-1, _sound, repeat ? -1 : 0, 0);
	}	
}

void SDL::Sound::Stop()
{

}
