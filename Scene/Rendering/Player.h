#pragma once
#include "Rect.h"

class Player final : public Rect
{
public:
	Player(Graphics* graphics, const D3DXCOLOR& color);
	~Player();

	virtual void Event() override;

private:
	virtual void Move() override;
	virtual void Restore() override;

	float speed = 4.0f;
};

