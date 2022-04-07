#include "GameOver.h"
#include "GameEngine.h"
#include "Sprite.h"
#include "Text.h"
#include "Button.h"

GameOver::GameOver(std::shared_ptr<GameEngine> engine)
{
	_engine = engine;

	_backgroundImg = std::make_unique<SDL::Sprite>(_engine, "Data/Images/gameOverMenu.png");

	_playAgainButton = std::make_unique<Button>(_engine, "Data/Images/playAgainButton.png");
	_playAgainButton->SetPosition(0, 394);
	_playAgainButton->CenterHorizontally(_engine->Width());
}

GameOver::~GameOver() = default;

void GameOver::Draw()
{
	_backgroundImg->Draw(CenterImgHorizontallyValue(*_backgroundImg), 145, 1);
	_playAgainButton->Draw();
}

bool GameOver::PlayAgainPressed(int mouseX, int mouseY)
{
	return _playAgainButton->IsInside(mouseX, mouseY);
}

int GameOver::CenterImgHorizontallyValue(SDL::Sprite img)
{
	return _engine->Width() / 2 - img.Width() / 2;
}
