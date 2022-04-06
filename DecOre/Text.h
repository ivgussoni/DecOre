#pragma once

#include <string>
#include <memory>

#include <SDL_ttf.h>

#include "GameEngine.h"
#include "GameWindow.h"
#include "Sprite.h"

using namespace std;
using namespace SDL;

namespace SDL
{
	class Text
	{
	public:
		Text(shared_ptr<GameWindow> window, string path, int fontSize);
		~Text();

		shared_ptr<Sprite> RenderText(string text, SDL_Color color);

	private:
		shared_ptr<GameWindow> _window = nullptr;

		string _filePath;

		int _size = 0;

		TTF_Font* _font = nullptr;

		void SetParams(shared_ptr<GameWindow> window, string path, int fontSize);

		shared_ptr<Sprite> ToImage(SDL_Surface* surf);
	};
}
