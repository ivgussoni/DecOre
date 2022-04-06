#pragma once

#include "Sprite.h"
#include <memory>

class GameEngine;

class Button
{
public:
	Button(std::shared_ptr<GameEngine> engine, std::string imgFilePath);
	~Button();

	void Draw();

	bool IsInside(int x, int y);

	void CenterHorizontally(int windowWidth);
	void SetPosition(int x, int y);

	int Height();
	int Width();

private:
	std::unique_ptr<SDL::Sprite> _image = nullptr;

	std::shared_ptr<GameEngine> _engine = nullptr;

	int _posX;
	int _posY;
};


