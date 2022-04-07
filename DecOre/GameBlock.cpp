#include "GameBlock.h"
#include "Sprite.h"

#include <iostream>

GameBlock::GameBlock()
{
	_animDestX = 0;
	_animDestY = 0;
	_animMaxMove = 0;
	_animOrientation = AnimationOrientation::Horizontal;
	_animOrigX = 0;
	_animOrigY = 0;
	_animStartTime = 0;

	_posX = 0;
	_posY = 0;
	_origX = 0;
	_origY = 0;
	_destX = 0;
	_destY = 0;

	_drawPosX = 0;
	_drawPosY = 0;

	_updatePosition = false;
	_updatePositionsCount = 0;

	Type = BlockType::Red;
	Empty = false;
	ToDestroy = false;
}

void GameBlock::Update()
{
	float animationSpeed = 0.f;

	switch (_animOrientation)
	{
		case AnimationOrientation::Horizontal:
		{
			animationSpeed = 200.f;
			break;
		}
		case AnimationOrientation::Vertical:
		{
			animationSpeed = 100.f * (_animDestY - _animOrigY);
			break;
		}		
		default:
			break;
	}

	if (_updatePosition)
	{
		Animate(animationSpeed);
	}

}

void GameBlock::Draw(int offsetX, int offsetY)
{
	if (!Empty)
	{
		_image->Draw((int)_drawPosX + offsetX, (int)_drawPosY + offsetY, 1);
	}
}

void GameBlock::SetPosition(float x, float y)
{
	_posX = x;
	_posY = y;

	_drawPosX = _posX * k_blockDrawSize;
	_drawPosY = _posY * k_blockDrawSize;
}

bool GameBlock::ToUpdate()
{
	return _updatePosition;
}

void GameBlock::IncrementUpdatePositionsCount()
{
	_updatePositionsCount++;
}

void GameBlock::SetUpdatePositionsCount(int drop)
{
	_updatePositionsCount = drop;
}

int GameBlock::UpdatePositionsCount()
{
	return _updatePositionsCount;
}

void GameBlock::SetImg(std::shared_ptr<SDL::Sprite> img)
{
	_image = img;
}

void GameBlock::Drop(int maxDrop)
{
	_animOrientation = AnimationOrientation::Vertical;
	_updatePosition = true;
	_animOrigX = _posX;
	_animOrigY = _posY;
	_animDestX = _posX;
	_animDestY = _posY + static_cast<float>(_updatePositionsCount);

	_animMaxMove = maxDrop;

	_animStartTime = SDL_GetTicks();
}

void GameBlock::ShiftLeft(int origX, int origY, int value, int maxShift)
{
	_animOrientation = AnimationOrientation::Horizontal;
	_updatePosition = true;
	_animOrigX = (float)origX;
	_animOrigY = (float)origY;
	_animDestX = (float)origX - value;
	_animDestY = (float)origY;

	_animMaxMove = maxShift;

	_animStartTime = SDL_GetTicks();
}

void GameBlock::ShiftRight(int origX, int origY, int value, int maxShift)
{
	_animOrientation = AnimationOrientation::Horizontal;
	_updatePosition = true;
	_animOrigX = (float)origX;
	_animOrigY = (float)origY;
	_animDestX = (float)origX + value;
	_animDestY = (float)origY;

	_animMaxMove = maxShift;

	_animStartTime = SDL_GetTicks();
}

void GameBlock::ResetState()
{
	ToDestroy = false;
	Empty = false;
}

void GameBlock::RectLerp(float f)
{
	float t = 1.0f - f;
	float x = _animOrigX == _animDestX ? _animOrigX : (float)_animOrigX * t + (float)_animDestX * f;
	float y = _animOrigY == _animDestY ? _animOrigY : (float)_animOrigY * t + (float)_animDestY * f;
	SetPosition(x, y);
}

bool GameBlock::Animate(float totalTime)
{
	int currentTime = SDL_GetTicks();
	bool isAnimationComplete = currentTime > _animStartTime + totalTime;

	if (isAnimationComplete)
	{
		SetPosition(_animDestX, _animDestY);
		_updatePosition = false;
		_updatePositionsCount = 0;
	}
	else
	{
		float factor = ((float)(currentTime - _animStartTime)) / totalTime;
		RectLerp(factor);
	}

	return isAnimationComplete;
}

