#include "Sprite.h"
#include "GameWindow.h"

SDL::Sprite::Sprite(std::shared_ptr<SDL::GameWindow> window, std::string filePath)
{
	SetWindow(window);
	SetPath(filePath);
}

SDL::Sprite::Sprite(std::shared_ptr<SDL::GameWindow> window, SDL_Texture* tex)
{
	SetWindow(window);
	SetTexture(tex);
}

SDL::Sprite::~Sprite()
{
	_containingWindow = nullptr;
	_texture = nullptr;
}

int SDL::Sprite::Width()
{
	return _width;
}

int SDL::Sprite::Height()
{
	return _height;
}

int SDL::Sprite::XPosition()
{
	return _posX;
}

int SDL::Sprite::YPosition()
{
	return _posY;
}

bool SDL::Sprite::Draw(int x, int y, int z, double factorX, double factorY)
{
	SDL_Rect destRect;
	destRect.w = int(_width * factorX);
	destRect.h = int(_height * factorY);
	destRect.x = x;
	destRect.y = y;

	int success = SDL_RenderCopyEx(_containingWindow->Renderer(), _texture.get(), nullptr, &destRect, 0, nullptr, SDL_FLIP_NONE);

	if (success == 0)
	{
		_posX = x;
		_posY = y;
	}

	return success == 0;
}

void SDL::Sprite::SetWindow(std::shared_ptr<SDL::GameWindow> window)
{
	_containingWindow = window;
}

void SDL::Sprite::SetPath(std::string filePath)
{
	_path = filePath;
	LoadTexture();
}

void SDL::Sprite::SetTexture(SDL_Texture* tex)
{
	_texture.reset(tex, DestroyTexture());
	SDL_QueryTexture(_texture.get(), nullptr, nullptr, &_width, &_height);
}

bool SDL::Sprite::VerifyParameters()
{
	return _containingWindow == nullptr && _path != "";
}

bool SDL::Sprite::LoadTexture()
{
	SDL_Texture* tex = IMG_LoadTexture(_containingWindow->Renderer(), _path.c_str());

	if (tex == nullptr)
	{
		return false;
	}

	SetTexture(tex);

	return true;
}
