#include "GameGrid.h"
#include "GameEngine.h"
#include "Sprite.h"
#include "GameBlock.h"
#include "Sound.h"
#include "GameScene.h"

#include <ctime>

GameGrid::GameGrid(std::shared_ptr<GameEngine> e)
{
	_engine = e;
	std::srand((unsigned)time(0));

	LoadResources();
	GenerateGrid();

	_updating = false;

	_currentState = GameState::Idle;
}

GameGrid::~GameGrid() = default;

void GameGrid::LoadResources()
{
	_blockRedImg = std::make_shared<SDL::Sprite>(_engine, "Data/Images/Block-red.png");
	_blockGreenImg = std::make_shared<SDL::Sprite>(_engine, "Data/Images/Block-green.png");
	_blockBlueImg = std::make_shared<SDL::Sprite>(_engine, "Data/Images/Block-blue.png");
	_blockGreyImg = std::make_shared<SDL::Sprite>(_engine, "Data/Images/Block-grey.png");
	_blockOrangeImg = std::make_shared<SDL::Sprite>(_engine, "Data/Images/Block-orange.png");

	_gameOverSound = std::make_unique<SDL::Sound>("Data/Sounds/gameOver.wav");
	_levelUpSound = std::make_unique<SDL::Sound>("Data/Sounds/levelUp.wav");
	_destroyBlocksSound = std::make_unique<SDL::Sound>("Data/Sounds/destroyBlocks.wav");
	_pushSound = std::make_unique<SDL::Sound>("Data/Sounds/push.wav");
	_generateBoardSound = std::make_unique<SDL::Sound>("Data/Sounds/generateBoard.wav");
}

void GameGrid::Update()
{
	for (int i = 0; i < k_boardWidth; ++i)
	{
		for (int j = 0; j < k_boardHeight; ++j)
		{
			if (!GetBlock(i, j)->Empty)
			{
				GetBlock(i, j)->Update();
			}
		}
	}

	if (!IsUpdating() && _stateQueue.size() != 0)
	{
		HandleState();
	}
}

void GameGrid::Draw()
{
	for (int i = 0; i < k_boardWidth; ++i)
	{
		for (int j = 0; j < k_boardHeight; ++j)
		{
			GetBlock(i, j)->Draw(k_gameDrawOffsetX, k_gameDrawOffsetY);
		}
	}
}

void GameGrid::GameOver()
{
	for (int y = 0; y < k_boardHeight; y++)
	{
		if (!GetBlock(0, y)->Empty)
		{
			GetBlock(0, y)->SetUpdatePositionsCount(k_boardHeight + 2);
			GetBlock(0, y)->Drop(k_boardHeight * 3);
		}
	}

	_gameOverSound->Play();
}

void GameGrid::HandleState()
{
	if (_currentState == GameState::GameOver)
	{
		return;
	}

	_currentState = _stateQueue.front();

	_stateQueue.pop();

	switch (_currentState)
	{
		case GameState::Idle:
		{
			break;
		}
		case GameState::DestroyBlocks:
		{
			DestroyBlocks();
			break;
		}
		case GameState::DropBlocks:
		{
			DropBlocks();
			break;
		}
		case GameState::CompactBlocks:
		{
			CompactBlocks();
			break;
		}
		case GameState::PushBlocks:
		{
			PushGrid();
			break;
		}
		case GameState::LevelUp:
		{
			LevelUpGrid();
			break;
		}
		case GameState::GenerateGrid:
		{
			GenerateGrid();
			break;
		}
		case GameState::GameOver:
		{
			GameOver();
			break;
		}
		default:
			break;
	}

	if (_stateQueue.size() == 0 && _currentState != GameState::GameOver)
	{
		_currentState = GameState::Idle;
	}
}

void GameGrid::GenerateGrid()
{
	CleanGrid();

	for (int i = k_boardWidth - k_initialBoardWidth; i < k_boardWidth; ++i)
	{
		for (int j = k_boardHeight - k_initialBoardHeight; j < k_boardHeight; ++j)
		{
			GenerateInitialRandomBlock(i, j);
		}
	}

	_generateBoardSound->Play();
}

void GameGrid::GenerateInitialRandomBlock(int x, int y)
{
	GetBlock(x, y)->Type = static_cast<GameBlock::BlockType>(rand() % 5);
	GetBlock(x, y)->SetPosition(static_cast<float>(x + k_initialBoardWidth), static_cast<float>(y));
	GetBlock(x, y)->SetImg(ImageForBlockType(GetBlock(x, y)->Type));
	GetBlock(x, y)->ShiftLeft(x + k_initialBoardWidth, y, k_initialBoardWidth, k_boardWidth);
	GetBlock(x, y)->ResetState();
}

void GameGrid::CleanGrid()
{
	for (int i = 0; i < k_boardWidth; ++i)
	{
		for (int j = 0; j < k_boardHeight; ++j)
		{
			GetBlock(i, j)->Empty = true;
		}
	}
}

int GameGrid::CheckSameTypeAdjacents(int x, int y)
{
	int result = 0;

	if (!GetBlock(x, y)->Empty)
	{
		//Check top block
		if (y != 0 && !GetBlock(x, y - 1)->Empty)
		{
			if (GetBlock(x, y - 1)->Type == GetBlock(x, y)->Type)
			{
				if (!GetBlock(x, y)->ToDestroy)
				{
					GetBlock(x, y)->ToDestroy = true;
					result++;
				}

				if (!GetBlock(x, y - 1)->ToDestroy)
				{
					result += CheckSameTypeAdjacents(x, y - 1);
				}
			}
		}

		//Check bottom block
		if (y != k_boardHeight - 1 && !GetBlock(x, y + 1)->Empty)
		{
			if (GetBlock(x, y + 1)->Type == GetBlock(x, y)->Type)
			{
				if (!GetBlock(x, y)->ToDestroy)
				{
					GetBlock(x, y)->ToDestroy = true;
					result++;
				}

				if (!GetBlock(x, y + 1)->ToDestroy) {
					result += CheckSameTypeAdjacents(x, y + 1);
				}
			}
		}

		//Check left block
		if (x != 0 && !GetBlock(x - 1, y)->Empty)
		{
			if (GetBlock(x - 1, y)->Type == GetBlock(x, y)->Type)
			{
				if (!GetBlock(x, y)->ToDestroy)
				{
					GetBlock(x, y)->ToDestroy = true;
					result++;
				}

				if (!GetBlock(x - 1, y)->ToDestroy)
				{
					result += CheckSameTypeAdjacents(x - 1, y);
				}
			}
		}

		//Check right block
		if (x != k_boardWidth - 1 && !GetBlock(x + 1, y)->Empty)
		{
			if (GetBlock(x + 1, y)->Type == GetBlock(x, y)->Type)
			{
				if (!GetBlock(x, y)->ToDestroy)
				{
					GetBlock(x, y)->ToDestroy = true;
					result++;
				}

				if (!GetBlock(x + 1, y)->ToDestroy)
				{
					result += CheckSameTypeAdjacents(x + 1, y);
				}
			}
		}
	}

	return result;
}

int GameGrid::DestroyBlocks()
{
	int blocksDestroyed = 0;

	//nested loopscare not recomended but well, the only solution that I can find right now
	for (int i = 0; i < k_boardWidth; i++)
	{
		for (int j = 0; j < k_boardHeight; j++)
		{
			if (!GetBlock(i, j)->Empty && GetBlock(i, j)->ToDestroy)
			{
				GetBlock(i, j)->Empty = true;
				blocksDestroyed++;
			}
		}
	}

	_destroyBlocksSound->Play();

	return blocksDestroyed;
}

void GameGrid::LevelUp()
{
	_stateQueue.push(GameState::LevelUp);
	_stateQueue.push(GameState::GenerateGrid);
}

void GameGrid::LevelUpGrid()
{
	//nested loopscare not recomended but well, the only solution that I can find right now
	for (int i = 0; i < k_boardWidth; ++i)
	{
		for (int j = 0; j < k_boardHeight; ++j)
		{
			if (!GetBlock(i, j)->Empty) 
			{
				GetBlock(i, j)->SetUpdatePositionsCount(k_boardHeight + 2);
				GetBlock(i, j)->Drop(k_boardHeight * 3);
			}
		}
	}

	_levelUpSound->Play();
}

void GameGrid::Push()
{
	_stateQueue.push(GameState::PushBlocks);
}

void GameGrid::PushGrid()
{
	if (!CheckEmptyColumn(0))
	{
		return;
	}

	_pushSound->Play();

	for (int x = 0; x < k_boardWidth; x++)
	{
		if (!CheckEmptyColumn(x))
		{
			for (int k = x; k < k_boardWidth; k++)
			{
				MoveColumn(k - 1, k, MoveDirection::Left);
			}

			GenerateNewColumn();

			if (!CheckEmptyColumn(0))
			{
				ClearStateQueue();
				_stateQueue.push(GameState::GameOver);
			}

			return;
		}
	}
}

GameBlock* GameGrid::GetBlock(int row, int column)
{
	int index = row + column * k_boardWidth;
	return &_blocks[index];
}

void GameGrid::CompactBlocks()
{
	for (int x = k_boardWidth - 1; x >= 0; x--)
	{
		bool keepSearching = false;

		if (CheckEmptyColumn(x))
		{
			for (int k = x - 1; k >= 0; k--)
			{
				if (!CheckEmptyColumn(k))
				{
					MoveColumn(x, k, MoveDirection::Right);
					keepSearching = true;
					break;
				}
			}

			if (!keepSearching) return;
		}
	}

}

void GameGrid::DropBlocks()
{
	for (int i = 0; i < k_boardWidth; i++)
	{
		bool dropsExist = false;

		//nested loopscare not recomended but well, the only solution that I can find right now
		for (int j = k_boardHeight - 1; j >= 0; j--)
		{
			if (GetBlock(i, j)->Empty)
			{
				for (int k = j - 1; k >= 0; k--)
				{
					//drops
					if (!GetBlock(i, k)->Empty)
					{
						GetBlock(i, k)->IncrementUpdatePositionsCount();
						dropsExist = true;
					}
				}
			}
		}

		if (dropsExist)
		{
			DropBlocksOfColumn(i);
		}
	}
}

void GameGrid::DropBlocksOfColumn(int x)
{
	for (int y = k_boardHeight - 1; y >= 0; y--)
	{
		if (!GetBlock(x, y)->Empty)
		{
			int drop = GetBlock(x, y)->UpdatePositionsCount();

			if (drop != 0)
			{
				*GetBlock(x, y + drop) = *GetBlock(x, y);

				//animation parameters
				GetBlock(x, y + drop)->Drop(k_boardHeight);
				GetBlock(x, y)->Empty = true;
			}

		}
	}
}

bool GameGrid::CheckEmptyColumn(int x)
{
	bool result = true;

	for (int y = k_boardHeight - 1; y >= 0; y--)
	{
		if (!GetBlock(x, y)->Empty)
		{
			result = false;
			return result;
		}
	}

	return result;
}

void GameGrid::MoveColumn(int destIndex, int origIndex, MoveDirection direction)
{
	for (int y = k_boardHeight - 1; y >= 0; y--)
	{
		*GetBlock(destIndex, y) = *GetBlock(origIndex, y);

		if (!GetBlock(destIndex, y)->Empty)
		{
			if (direction == MoveDirection::Left)
			{
				GetBlock(destIndex, y)->ShiftLeft(destIndex + 1, y, 1, k_boardWidth);
			}
			else if (direction == MoveDirection::Right)
			{
				GetBlock(destIndex, y)->ShiftRight(origIndex, y, destIndex - origIndex, k_boardWidth);
			}
		}

		GetBlock(origIndex, y)->Empty = true;
	}
}

void GameGrid::GenerateNewColumn()
{
	for (int y = k_boardHeight - 1; y >= 0; y--)
	{
		GenerateRandomNewColumnBlock(y);
	}
}

void GameGrid::GenerateRandomNewColumnBlock(int y)
{
	GetBlock(k_boardWidth - 1, y)->Type = static_cast<GameBlock::BlockType>(rand() % 5);
	GetBlock(k_boardWidth - 1, y)->SetPosition(static_cast<float>(k_boardWidth), static_cast<float>(y));
	GetBlock(k_boardWidth - 1, y)->SetImg(ImageForBlockType(GetBlock(k_boardWidth - 1, y)->Type));
	GetBlock(k_boardWidth - 1, y)->ShiftLeft(k_boardWidth, y, 1, k_boardWidth);
	GetBlock(k_boardWidth - 1, y)->ResetState();
}

void GameGrid::Reset()
{
	ClearStateQueue();
	_currentState = GameState::Idle;
	GenerateGrid();
}

int GameGrid::HandleBlockClick(int x, int y)
{
	int blocksDestroyed = CheckSameTypeAdjacents(x, y);

	if (blocksDestroyed > 0)
	{
		_stateQueue.push(GameState::DestroyBlocks);
		_stateQueue.push(GameState::DropBlocks);
		_stateQueue.push(GameState::CompactBlocks);
	}

	return blocksDestroyed;
}

std::shared_ptr<SDL::Sprite> GameGrid::ImageForBlockType(GameBlock::BlockType type)
{
	switch (type)
	{
		case GameBlock::BlockType::Red:
		{
			return _blockRedImg;
		}
		case GameBlock::BlockType::Green:
		{
			return _blockGreenImg;
		}
		case GameBlock::BlockType::Blue:
		{
			return _blockBlueImg;
		}
		case GameBlock::BlockType::Grey:
		{
			return _blockGreyImg;
		}
		case GameBlock::BlockType::Orange:
		{
			return _blockOrangeImg;
		}
		default:
			break;
	}

	return _blockRedImg;
}

bool GameGrid::IsUpdating()
{
	bool result = false;

	//nested loopscare not recomended but well, the only solution that I can find right now
	for (int i = 0; i < k_boardWidth; ++i)
	{
		for (int j = 0; j < k_boardHeight; ++j)
		{
			if (!GetBlock(i, j)->Empty && GetBlock(i, j)->ToUpdate())
			{
				result = true;
				break;
				break;
			}
		}
	}

	return result;
}

GameGrid::GameState GameGrid::State()
{
	return _currentState;
}

void GameGrid::ClearStateQueue()
{
	std::queue<GameState> empty;
	std::swap(_stateQueue, empty);
}
