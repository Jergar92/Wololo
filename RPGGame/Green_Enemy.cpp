#include "Application.h"
#include "Green_Enemy.h"
#include "ModuleCollider.h"
#include "ModuleRender.h"
#include "stdlib.h"
#include "ModuleLevel1.h"
#include <time.h>

Green_Enemy::Green_Enemy(int x, int y, int hp, int attack, int defense, int at_delay, int mov_delay) :Enemy(x, y, hp, attack, defense, at_delay, mov_delay)
{
	position.x = x;
	position.y = y;

	close.PushBack({ 1183, 27, 109, 109 });
	medium.PushBack({ 646, 149, 57, 57 });

	//To modify
	distant.PushBack({ 16, 225, 77, 105 });

	animation_close = &close;
	animation_medium = &medium;
	animation_distant = &distant;
}

void Green_Enemy::Move()
{
	if (actual_time >= timer + mov_delay)
	{
		timer = actual_time;
		srand(time(NULL));

		int dir = rand() % 4;

		switch (dir)
		{
			//NORTH
		case 0:
		{
			if (App->level1->map[position.y - 1][position.x] != 0)
			{
				position.y -= 1;
				LOG("Moved to NORTH");
			}
			break;
		}
		//EAST
		case 1:
		{
			if (App->level1->map[position.y][position.x + 1] != 0)
			{
				position.x += 1;
				LOG("Moved to EAST");
			}
			break;
		}
		//SOUTH
		case 2:
		{
			if (App->level1->map[position.y + 1][position.x] != 0)
			{
				position.y += 1;
				LOG("Moved to SOUTH");
			}
			break;
		}
		//WEST
		case 3:
		{
			if (App->level1->map[position.y][position.x - 1] != 0)
			{
				position.x -= 1;
				LOG("Moved to WEST");
			}
			break;
		}
		default:
		{
			LOG("NO MOVEMENT");
			break;
		}
		}
	}
}
