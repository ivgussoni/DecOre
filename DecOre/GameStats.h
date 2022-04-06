#pragma once

#include <memory>

#include "Sprite.h"
#include "Text.h"
#include "GameEngine.h"

class GameStats
{
public:
	GameStats(std::shared_ptr<GameEngine> engine);
	~GameStats();

	void Draw();

	void UpdateScore(int score);
	void UpdateLevel(int level);

	void UpdateLevelBar(int score, int prevLevelScore, int nextLevelScore);
	void UpdatePushBar(int pushTime, int actualTime);

private:
	std::shared_ptr<SDL::Sprite> _scoreImg = nullptr;
	std::shared_ptr<SDL::Sprite> _levelImg = nullptr;
	std::unique_ptr<SDL::Sprite> _levelBar = nullptr;
	std::unique_ptr<SDL::Sprite> _pushBar = nullptr;

	std::unique_ptr<SDL::Text> _fontUI = nullptr;

	float _pushBarPercentage = 0.0f;
	float _levelBarPercentage = 0.0f;

	std::shared_ptr<GameEngine> _engine = nullptr;

};
