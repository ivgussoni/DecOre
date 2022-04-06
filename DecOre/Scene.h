#pragma once

#include <SDL.h>
#include <memory>

class GameEngine;

class Scene
{
protected:
	std::shared_ptr<GameEngine> g_engine;

public:
	Scene(std::shared_ptr<GameEngine> engine_instance);
	virtual ~Scene() {};

	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void MouseButtonDown(Uint8) { }
};