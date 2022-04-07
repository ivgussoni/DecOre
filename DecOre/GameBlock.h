#pragma once

#include "Sprite.h"
#include <memory>

static const int k_blockDrawSize = 40;

class GameBlock
{
public:
	enum class BlockType
	{
		Red,
		Green,
		Blue,
		Grey,
		Orange
	};

	enum class AnimationOrientation
	{
		Horizontal,
		Vertical
	};

	GameBlock();

	BlockType Type;
	bool Empty;
	bool ToDestroy;

	void Update();
	void Draw(int offsetX, int offsetY);

	void SetPosition(float x, float y);

	bool ToUpdate();

	void IncrementUpdatePositionsCount();
	void SetUpdatePositionsCount(int drop);
	int UpdatePositionsCount();

	void SetImg(std::shared_ptr<SDL::Sprite> img);

	void Drop(int maxDrop);

	void ShiftLeft(int origX, int origY, int value, int maxShift);
	void ShiftRight(int origX, int origY, int value, int maxShift);

	void ResetState();

private:
	float _posX;
	float _posY;

	float _drawPosX;
	float _drawPosY;

	float _animOrigX;
	float _animOrigY;

	float _animDestX;
	float _animDestY;

	int _animMaxMove;
	AnimationOrientation _animOrientation;

	int _animStartTime;

	bool _updatePosition;

	int _origX;
	int _origY;

	int _destX;
	int _destY;

	int _updatePositionsCount;

	std::shared_ptr<SDL::Sprite> _image = nullptr;

	void RectLerp(float f);

	bool Animate(float totalTime);
};