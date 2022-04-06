#pragma once

#include <string>
#include <memory>

#include "GameWindow.h"

class Scene;

class GameEngine : public SDL::GameWindow, public std::enable_shared_from_this<GameEngine>
{
	public:

		enum class SceneId
		{
			None,
			MainMenu,
			Game
		};

		GameEngine();
		~GameEngine();

		void Close() override;
		void Update();
		void Draw();

		void Run();

		void MouseButtonDown(Uint8 button);

		void SwitchScene(SceneId sceneID);

	private:

		std::unique_ptr<Scene> _currentScene = nullptr;
		SceneId _currentSceneId = SceneId::None;		
};

