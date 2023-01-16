#include "stdafx.h"
#include "Monster.h"

Monster::Monster(Graphics* graphics, const D3DXCOLOR& color)
	:Rect(graphics, color)
{
	direction = static_cast<Direction>(Math::Random(Direction::MIN, Direction::MAX));
}

Monster::~Monster()
{
}

void Monster::Move()
{
	return;

	switch (direction)
	{
	case Direction::U:
		position.x += +0;
		position.y += +1;
		break;
	case Direction::UR:
		position.x += +1;
		position.y += +1;
		break;
	case Direction::R:
		position.x += +1;
		position.y += +0;
		break;
	case Direction::UL:
		position.x += -1;
		position.y += +1;
		break;
	case Direction::D:
		position.x += +0;
		position.y += -1;
		break;
	case Direction::DL:
		position.x += -1;
		position.y += -1;
		break;
	case Direction::L:
		position.x += -1;
		position.y += +0;
		break;
	case Direction::DR:
		position.x += +1;
		position.y += -1;
		break;
	default:
		break;
	}

	int window_width = Settings::Get().GetWidth() / 2;
	int window_height = Settings::Get().GetHeight() / 2;

	if (position.x >= window_width
		|| position.x <= -window_width
		|| position.y >= window_height
		|| position.y <= -window_height
		)
	{
		int random_x = Math::Random(-window_width, window_width);
		int random_y = Math::Random(-window_height, window_height);

		position.x = random_x;
		position.y = random_y;
	}

	if (stopwatch.GetElapsedTimeMs() >= 2000.0)
	{
		Direction new_dir = static_cast<Direction>(Math::Random(Direction::MIN, Direction::MAX));

		if (direction == new_dir)
		{
			int dir_num = static_cast<int>(new_dir);
			int middle = Direction::COUNT / 2;

			dir_num = (dir_num < middle) ? dir_num + middle : dir_num - middle;

			direction = static_cast<Direction>(dir_num);
		}
		else
			direction = new_dir;

		stopwatch.Start();
	}
}

void Monster::Restore()
{
	int window_width = Settings::Get().GetWidth() / 2;
	int window_height = Settings::Get().GetHeight() / 2;

	int random_x = Math::Random(-window_width, window_width);
	int random_y = Math::Random(-window_height, window_height);

	position.x = random_x;
	position.y = random_y;

	is_active = true;
}

void Monster::Event()
{
	is_active = false;

	is_intersect = true;
	restore_stopwatch.Start();
}
