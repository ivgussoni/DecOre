#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <string>

namespace SDL 
{
	class GameWindow
	{
	public:
		GameWindow(unsigned width, unsigned height, std::string title);
		~GameWindow();

		void Show();
		virtual void Close();

		virtual void Update() = 0;
		virtual void Draw() = 0;

		virtual void MouseButtonDown(Uint8) { }

		int MouseX();
		int MouseY();

		SDL_Renderer* Renderer();

		int Width();
		int Height();

	private:
		unsigned _width;
		unsigned _height;

		std::string _title;

		bool _runGame;

		SDL_Window* _window = nullptr;

		SDL_Renderer* _renderer = nullptr;

		void StartSDL();

		void QuitSDL();

		void Setup();
		void SetupWindow();
		void InitTTF();
		void InitMixer();
		void InitPNGLoading();
		void SetLinearTextureFiltering();

		void RunGameLoop();
		void HandleSDLEvents(SDL_Event& event, bool& shouldQuit);
	};
}


