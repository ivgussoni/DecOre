#pragma once

#include <array>
#include <queue>
#include <string>

#include "GameBlock.h"
#include "Sprite.h"

static const unsigned int k_boardWidth = 17;
static const unsigned int k_boardHeight = 10;
static const unsigned int k_initialBoardWidth = 8;
static const unsigned int k_initialBoardHeight = 10;

static const unsigned int k_gameDrawOffsetX = 120;
static const unsigned int k_gameDrawOffsetY = 126;

class GameEngine;

namespace SDL
{
	class Sound;
};

class GameGrid
{
public:
	enum class GameState
	{
		Idle,
		DestroyBlocks,
		DropBlocks,
		CompactBlocks,
		PushBlocks,
		LevelUp,
		GenerateGrid,
		GameOver
	};

	GameGrid(std::shared_ptr<GameEngine> e);
	~GameGrid();

	void Update();
	void Draw();

	void Push();

	int HandleBlockClick(int x, int y);

	void LevelUp();

	GameState State();

	void ClearStateQueue();

	void Reset();

private:
	enum class MoveDirection
	{
		Left,
		Right
	};

	std::array<GameBlock, k_boardWidth* k_boardHeight> _blocks;

	std::queue<GameState> _stateQueue;

	GameState _currentState;

	std::shared_ptr<SDL::Sprite> _blockRedImg = nullptr;
	std::shared_ptr<SDL::Sprite> _blockGreenImg = nullptr;
	std::shared_ptr<SDL::Sprite> _blockBlueImg = nullptr;
	std::shared_ptr<SDL::Sprite> _blockGreyImg = nullptr;
	std::shared_ptr<SDL::Sprite> _blockOrangeImg = nullptr;

	std::unique_ptr<SDL::Sound> _gameOverSound = nullptr;
	std::unique_ptr<SDL::Sound> _levelUpSound = nullptr;
	std::unique_ptr<SDL::Sound> _destroyBlocksSound = nullptr;
	std::unique_ptr<SDL::Sound> _pushSound = nullptr;
	std::unique_ptr<SDL::Sound> _generateBoardSound = nullptr;

	bool _updating;

	std::shared_ptr<GameEngine> _engine = nullptr;

	void LoadResources();

	bool IsUpdating();

	void GenerateGrid();
	void CleanGrid();

	void GenerateInitialRandomBlock(int x, int y);
	void GenerateRandomNewColumnBlock(int y);

	void GameOver();

	std::shared_ptr<SDL::Sprite> ImageForBlockType(GameBlock::BlockType type);

	int CheckSameTypeAdjacents(int x, int y);

	int DestroyBlocks();
	void DropBlocks();
	void DropBlocksOfColumn(int x);
	void CompactBlocks();

	bool CheckEmptyColumn(int x);
	void MoveColumn(int destIndex, int origIndex, MoveDirection direction);
	void GenerateNewColumn();

	void HandleState();

	void LevelUpGrid();
	void PushGrid();

	GameBlock* GetBlock(int row, int column);
};



