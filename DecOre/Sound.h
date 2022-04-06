#pragma once

#include <string>

#include <SDL_mixer.h>

namespace SDL
{
	class Sound
	{
	public:
		Sound(std::string filePath);
		~Sound();

		void Play(float volume = 1, bool repeat = false);
		void Stop();

	private:
		Mix_Chunk* _sound = nullptr;

		void SetPath(std::string filePath);
	};
}

