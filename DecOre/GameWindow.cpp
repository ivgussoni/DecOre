#include "GameWindow.h"

#include <iostream>
#include <stdexcept>

using namespace std;

SDL::GameWindow::GameWindow(unsigned width, unsigned height, std::string title)
{
	_width = width;
	_height = height;
	_title = title;

	Setup();
}

SDL::GameWindow::~GameWindow()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	_renderer = nullptr;
	_window = nullptr;

	QuitSDL();
}

void SDL::GameWindow::Show()
{
	SDL_ShowWindow(_window);

	_runGame = true;

	RunGameLoop();
}

void SDL::GameWindow::Close()
{
	_runGame = false;
}

int SDL::GameWindow::MouseX()
{
	int x;
	SDL_GetMouseState(&x, NULL);

	return x;
}

int SDL::GameWindow::MouseY()
{
	int y;
	SDL_GetMouseState(NULL, &y);

	return y;
}

SDL_Renderer* SDL::GameWindow::Renderer()
{
	return _renderer;
}

int SDL::GameWindow::Width()
{
	return _width;
}

int SDL::GameWindow::Height()
{
	return _height;
}

void SDL::GameWindow::StartSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		throw std::runtime_error(SDL_GetError());
	}
}

void SDL::GameWindow::QuitSDL()
{
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void SDL::GameWindow::Setup()
{
	StartSDL();
	SetLinearTextureFiltering();
	InitPNGLoading();
	InitTTF();
	InitMixer();
	SetupWindow();
}

void SDL::GameWindow::SetupWindow()
{
	_window = SDL_CreateWindow(PROJECT_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN);

	if (_window == nullptr)
	{
		throw std::runtime_error(SDL_GetError());
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (_renderer == nullptr)
	{
		throw std::runtime_error(SDL_GetError());
	}

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}

void SDL::GameWindow::InitTTF()
{
	TTF_Init();
}

void SDL::GameWindow::InitMixer()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		throw std::runtime_error(Mix_GetError());
	}
}

void SDL::GameWindow::InitPNGLoading()
{
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		throw std::runtime_error(IMG_GetError());
	}
}

void SDL::GameWindow::SetLinearTextureFiltering()
{
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

void SDL::GameWindow::RunGameLoop()
{
	SDL_Event event;

	while (_runGame)
	{
		bool shouldQuit;

		HandleSDLEvents(event, shouldQuit);

		if (shouldQuit)
		{
			return;
		}

		Update();
		SDL_RenderClear(_renderer);
		Draw();
		SDL_RenderPresent(_renderer);
	}
}

void SDL::GameWindow::HandleSDLEvents(SDL_Event& event, bool& shouldQuit)
{
	shouldQuit = false;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Close();
			shouldQuit = true;

		case SDL_MOUSEBUTTONDOWN:
			MouseButtonDown(event.button.button);
			break;
		}
	}
}
