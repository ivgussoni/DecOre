#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <memory>

#include "GameWindow.h"

using namespace std;

namespace SDL 
{
	class Sprite
	{
	public:
		Sprite(std::shared_ptr<SDL::GameWindow> window, std::string filePath);
		Sprite(std::shared_ptr<SDL::GameWindow> window, SDL_Texture* tex);
		~Sprite();

		int Width();
		int Height();

		int XPosition();
		int YPosition();

		bool Draw(int x, int y, int z, double factorX = 1, double factorY = 1);

	private:
		std::shared_ptr<SDL::GameWindow> _containingWindow = nullptr;

		int _width;
		int _height;

		int _posX;
		int _posY;

		std::string _path;

		std::shared_ptr<SDL_Texture> _texture = nullptr;

		struct DestroyTexture
		{
			void operator()(SDL_Texture* texture) const
			{
				if (texture)
				{
					SDL_DestroyTexture(texture);
				}
			}
		};

		void SetWindow(std::shared_ptr<SDL::GameWindow> window);

		void SetPath(std::string filePath);

		void SetTexture(SDL_Texture* tex);

		bool VerifyParameters();

		bool LoadTexture();
	};
}

