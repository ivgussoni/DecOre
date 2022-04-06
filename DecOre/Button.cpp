#include "Button.h"
#include "GameEngine.h"

Button::Button(std::shared_ptr<GameEngine> engine, std::string imgFilePath)
{
	_engine = engine;
	_image = std::make_unique<SDL::Sprite>(_engine, imgFilePath);
}

Button::~Button() = default;

void Button::Draw()
{
	_image->Draw(_posX, _posY, 1);
}

bool Button::IsInside(int x, int y)
{
	if (x >= _posX && x <= _posX + _image->Width()
		&& y >= _posY && y <= _posY + _image->Height())
	{
		return true;
	}
	else {
		return false;
	}
}

void Button::CenterHorizontally(int windowWidth)
{
	_posX = windowWidth / 2 - _image->Width() / 2;
}

void Button::SetPosition(int x, int y)
{
	_posX = x;
	_posY = y;
}

int Button::Height()
{
	return _image->Height();
}

int Button::Width()
{
	return _image->Width();
}
