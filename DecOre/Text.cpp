#include "Text.h"
#include "GameWindow.h"
#include "Sprite.h"

#include <iostream>

Text::Text(shared_ptr<GameWindow> window, string path, int fontSize)
{
	SetParams(window, path, fontSize);
}

Text::~Text()
{
	TTF_CloseFont(_font);
	_font = nullptr;
}

void Text::SetParams(shared_ptr<GameWindow> window, string path, int fontSize)
{
	_window = window;
	_filePath = path;
	_size = fontSize;

	_font = TTF_OpenFont(_filePath.c_str(), _size);

	if (_font == nullptr)
	{
		cerr << TTF_GetError();
	}
}

shared_ptr<Sprite> Text::RenderText(string text, SDL_Color color)
{
	SDL_Surface* surf = TTF_RenderUTF8_Blended(_font, text.c_str(), color);
	return ToImage(surf);
}

shared_ptr<Sprite> Text::ToImage(SDL_Surface* surf)
{
	SDL_Texture* text = SDL_CreateTextureFromSurface(_window->Renderer(), surf);

	SDL_FreeSurface(surf);

	shared_ptr<Sprite> resultImg = make_shared<Sprite>(_window, text);

	return resultImg;
}
