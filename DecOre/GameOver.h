#pragma once
#include<memory>

namespace SDL
{
	class Text;
	class Sprite;
}

class GameEngine;
class Button;

class GameOver
{
public:
	GameOver(std::shared_ptr<GameEngine> e);
	~GameOver();

	void Draw();

	bool PlayAgainPressed(int mouseX, int mouseY);

private:

	std::unique_ptr<SDL::Sprite> _backgroundImg = nullptr;
	std::shared_ptr<SDL::Sprite> _scoreImg = nullptr;
	std::shared_ptr<SDL::Sprite> _levelImg = nullptr;

	std::unique_ptr<Button> _playAgainButton;

	std::unique_ptr<SDL::Text> _fontUI = nullptr;
	
	std::shared_ptr<GameEngine> _engine = nullptr;

	int CenterImgHorizontallyValue(SDL::Sprite img);
};

