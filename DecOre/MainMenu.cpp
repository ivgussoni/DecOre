#include "MainMenu.h"
#include "GameEngine.h"

MainMenu::MainMenu(std::shared_ptr<GameEngine> g_engine) : Scene(g_engine)
{
	_backgroundImg = std::make_unique<SDL::Sprite>(g_engine, "Assets/Images/menuBackground.png");

	_playButton = std::make_unique<Button>(g_engine, "Assets/Images/playButton.png");
	_playButton->SetPosition(0, g_engine->Height() - _playButton->Height() - 20);
	_playButton->CenterHorizontally(g_engine->Width());

	//_introSound = std::make_unique<SDL::Sound>("Assets/Sounds/intro.wav");
	//_introSound->Play();
}

MainMenu::~MainMenu() = default;

void MainMenu::Update()
{
}

void MainMenu::Draw()
{
	_backgroundImg->Draw(0, 0, 1);
	_playButton->Draw();
}

void MainMenu::MouseButtonDown(Uint8 button)
{
	if (button == SDL_BUTTON_LEFT)
	{
		int y = g_engine->MouseY();
		int x = g_engine->MouseX();

		if (_playButton->IsInside(x, y))
		{
			g_engine->SwitchScene(GameEngine::SceneId::Game);
		}
	}
}
