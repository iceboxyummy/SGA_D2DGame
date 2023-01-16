#pragma once
#include "Rect.h"
class Monster final : public Rect
{
public:
	Monster(Graphics* graphics, const D3DXCOLOR& color);
	~Monster();

	virtual void Event() override;

private:
	virtual void Move() override;
	virtual void Restore() override;

private:
	Stopwatch stopwatch;
	Direction direction = Direction::R;
};

