#pragma once

#include <memory>

#include "Scene.h"
#include "GameEngine.h"
#include "Sprite.h"
#include "Sound.h"
#include "Button.h"

class MainMenu : public Scene
{
public:
	MainMenu(std::shared_ptr<GameEngine> g_engine);
	~MainMenu();

	void Update();
	void Draw();

	void MouseButtonDown(Uint8 button);

private:
	std::unique_ptr<SDL::Sprite> _backgroundImg = nullptr;
	std::unique_ptr<Button> _playButton = nullptr;
	std::unique_ptr<SDL::Sound> _introSound = nullptr;
};
