#include "Local_DEFINES.h"

#include "MainMenu.h"
#include "GameScene.h"
#include "GameEngine.h"
#include "Scene.h"

GameEngine::GameEngine() : SDL::GameWindow(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT, PROJECT_NAME) 
{

};

GameEngine::~GameEngine() = default;

void GameEngine::Close()
{
	GameWindow::Close();
	_currentScene.reset();
}

void GameEngine::Update()
{
	//We MUST check if the ptr is not null to avoid crashes.
	if (_currentScene != nullptr)
	{
		_currentScene->Update();
	}
}

void GameEngine::Draw()
{
	//We MUST check if the ptr is not null to avoid crashes.
	if (_currentScene != nullptr)
	{
		_currentScene->Draw();
	}
}

void GameEngine::Run()
{
	SwitchScene(SceneId::MainMenu);
	Show();
}

void GameEngine::MouseButtonDown(Uint8 button)
{
	//We MUST check if the ptr is not null to avoid crashes.
	if (_currentScene != nullptr)
	{
		_currentScene->MouseButtonDown(button);
	}
}

void GameEngine::SwitchScene(SceneId sceneID)
{
	if (sceneID != _currentSceneId)
	{
		auto const wptr = std::shared_ptr<GameEngine>(this, [](GameEngine*) {});

		switch (sceneID)
		{
		case SceneId::MainMenu:
			_currentScene = std::make_unique<MainMenu>(shared_from_this());
			_currentSceneId = sceneID;
			break;
		case SceneId::Game:
			_currentScene = std::make_unique<GameScene>(shared_from_this());
			_currentSceneId = sceneID;
			break;
		default:
			break;
		}
	}
}
