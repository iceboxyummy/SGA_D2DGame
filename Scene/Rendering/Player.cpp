#include "stdafx.h"
#include "Player.h"

Player::Player(Graphics* graphics, const D3DXCOLOR& color)
	: Rect(graphics, color)
{
}

Player::~Player()
{
}

void Player::Move()
{
	if (GetAsyncKeyState('W') & 0x8000) position.y += speed;
	if (GetAsyncKeyState('S') & 0x8000) position.y -= speed;
	if (GetAsyncKeyState('D') & 0x8000) position.x += speed;
	if (GetAsyncKeyState('A') & 0x8000) position.x -= speed;
}

void Player::Restore()
{
	intersect_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	speed = 4.0;
}

void Player::Event()
{
	intersect_color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	speed *= 0.9;

	is_intersect = true;
	restore_stopwatch.Start();
}
