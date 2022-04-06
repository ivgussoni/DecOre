#include "GameStats.h"

#include <iostream>

static const int k_levelBarPosX = 340;
static const int k_levelBarPosY = 19;

static const int k_pushBarPosX = 585;
static const int k_pushBarPosY = 19;

static const int k_scorePosX = 105;
static const int k_scorePosY = 16;

static const int k_levelPosX = 310;
static const int k_levelPosY = 16;

GameStats::GameStats(std::shared_ptr<GameEngine> engine)
{
	_engine = engine;
	_levelBar = std::make_unique<SDL::Sprite>(_engine, "Assets/Images/ProgressBar.png");

	_pushBar = std::make_unique<SDL::Sprite>(_engine, "Assets/Images/PushBar.png");

	_fontUI = std::make_unique<SDL::Text>(_engine, "Assets/Fonts/pixelart.ttf", 20);

	_scoreImg = _fontUI->RenderText(std::to_string(0), { 255, 255, 255, 255 });
	_levelImg = _fontUI->RenderText(std::to_string(1), { 255, 255, 255, 255 });

	_levelBarPercentage = 0.0f;
	_pushBarPercentage = 0.0f;
}

GameStats::~GameStats() = default;

void GameStats::Draw()
{
	_levelBar->Draw(k_levelBarPosX, k_levelBarPosY, 1, _levelBarPercentage);
	_pushBar->Draw(k_pushBarPosX, k_pushBarPosY, 1, _pushBarPercentage);

	_scoreImg->Draw(k_scorePosX, k_scorePosY, 1);
	_levelImg->Draw(k_levelPosX, k_levelPosY, 1);
}

void GameStats::UpdateScore(int score)
{
	_scoreImg = _fontUI->RenderText(std::to_string(score), { 255, 255, 255, 255 });
}

void GameStats::UpdateLevel(int level)
{
	_levelImg = _fontUI->RenderText(std::to_string(level), { 255, 255, 255, 255 });
}

void GameStats::UpdateLevelBar(int score, int prevLevelScore, int nextLevelScore)
{
	float adjustedScore = static_cast<float>(score - prevLevelScore);
	float adjustedNextLevel = static_cast<float>(nextLevelScore - prevLevelScore);

	_levelBarPercentage = adjustedScore / adjustedNextLevel;
}

void GameStats::UpdatePushBar(int pushTime, int actualTime)
{
	_pushBarPercentage = static_cast<float>(actualTime) / static_cast<float>(pushTime);
}
