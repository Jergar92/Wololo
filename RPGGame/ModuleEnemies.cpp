#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTexture.h"
#include "Enemy.h"
#include "Blue_Enemy.h"
#include "ModuleLevel1.h"
#include "ModulePlayer.h"
#include "Blue_Enemy.h"
#include "Red_Enemy.h"
#include "Green_Enemy.h"

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		enemies[i] = nullptr;
	}
}

ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	sprites = App->texture->Load("Enemies_FINAL.png");
	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; i++)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			SpawnEnemy(queue[i]);
			queue[i].type = ENEMY_TYPES::NO_TYPE;
			LOG("Spawning enemy at [%i][%i]\n", App->enemies->queue[i].y, App->enemies->queue[i].x);
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; i++)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->actual_time = GetTickCount();
		}
	}

	for (uint i = 0; i < MAX_ENEMIES; i++)
	{
		if (enemies[i] != nullptr)
		{			
			if (enemies[i]->EnemyCanGoTo()){
				enemies[i]->Move();
			}
			else{
				enemies[i]->Rotation();
			}
			
		}
	}
	for (uint i = 0; i < MAX_ENEMIES; i++)
	{
		if (enemies[i] != nullptr)
		{
			if (App->player->dir == NORTH)
			{
				if (checkMonster(App->player->position.x, App->player->position.y - 1, i))
				{
					if (canSeePlayer(App->player->position.x, App->player->position.y - 1, i)){
						formationOrder(i);
						enemies[i]->Draw_close(sprites);
					}
				}
				if (checkMonster(App->player->position.x, App->player->position.y - 2, i))
				{
					if (canSeePlayer(App->player->position.x, App->player->position.y - 2, i)){
						formationOrder(i);
						enemies[i]->Draw_medium(sprites);
					}
				}
			}
			else if (App->player->dir == EAST)
			{
				if (checkMonster(App->player->position.x + 1, App->player->position.y, i))
				{
					if (canSeePlayer(App->player->position.x + 1, App->player->position.y, i)){
						formationOrder(i);
						enemies[i]->Draw_close(sprites);
					}
				}
				if (checkMonster(App->player->position.x + 2, App->player->position.y, i))
				{
					if (canSeePlayer(App->player->position.x + 2, App->player->position.y, i)){
						formationOrder(i);
						enemies[i]->Draw_medium(sprites);
					}
				}
			}
			else if (App->player->dir == SOUTH)
			{
				if (checkMonster(App->player->position.x, App->player->position.y + 1, i))
				{
					if (canSeePlayer(App->player->position.x, App->player->position.y + 1, i)){
						formationOrder(i);
						enemies[i]->Draw_close(sprites);
					}
				}
				if (checkMonster(App->player->position.x, App->player->position.y + 2, i))
				{
					if (canSeePlayer(App->player->position.x, App->player->position.y + 2, i)){
						formationOrder(i);
						enemies[i]->Draw_medium(sprites);
					}
				}
			}
			else if (App->player->dir == WEST)
			{
				if (checkMonster(App->player->position.x - 1, App->player->position.y, i))
				{
					if (canSeePlayer(App->player->position.x - 1, App->player->position.y, i)){
						formationOrder(i);
						enemies[i]->Draw_close(sprites);
					}
				}
				if (checkMonster(App->player->position.x - 2, App->player->position.y, i))
				{
					if (canSeePlayer(App->player->position.x - 2, App->player->position.y, i)){
						formationOrder(i);
						enemies[i]->Draw_medium(sprites);
					}
				}
			}
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; i++)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->hp <= 0)
			{
				LOG("Enemy died at[%i][%i]\n", App->enemies->queue[i].y, App->enemies->queue[i].x);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}
	return UPDATE_CONTINUE;
}

bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");
	App->texture->Unload(sprites);

	for (uint i = 0; i < MAX_ENEMIES; i++)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}
	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, int hp, int attack, int defense, int at_delay, int mov_delay,direction direction)
{
	bool ret = false;
	for (uint i = 0; i < MAX_ENEMIES; i++)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].hp = hp;
			queue[i].attack = attack;
			queue[i].defense = defense;
			queue[i].at_delay = at_delay;
			queue[i].mov_delay = mov_delay;
			queue[i].dir = direction;

			ret = true;
			break;
		}
	}
	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; i++);
	
	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::BLUE:
		{
			enemies[i] = new Blue_Enemy(info.x, info.y, info.hp, info.attack, info.defense, info.at_delay, info.mov_delay,info.dir);
			break;
		}
		case ENEMY_TYPES::RED:
		{
			enemies[i] = new Red_Enemy(info.x, info.y, info.hp, info.attack, info.defense, info.at_delay, info.mov_delay, info.dir);
			break;
		}
		case ENEMY_TYPES::GREEN:
		{
			enemies[i] = new Green_Enemy(info.x, info.y, info.hp, info.attack, info.defense, info.at_delay, info.mov_delay, info.dir);
			break;
		}
		}
	}
}

//void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)

bool ModuleEnemies::checkMonster(int x, int y, int i)
{
	bool ret = false;
	if (enemies[i] != nullptr)
	{
		if (enemies[i]->position.x == x && enemies[i]->position.y == y)
		{
			ret = true;
		}
	}
	return ret;
}

bool ModuleEnemies::canSeePlayer(int x, int y, int i)
{
	int checkY = y, checkX = x;
	bool ret = true;
	if (queue[i].x == checkX && queue[i].y == checkY)
		{
			while ((App->player->position.y != checkY) || (App->player->position.x != checkX)){

				if (App->level1->map[checkY][checkX] == 0 || App->level1->map[checkY][checkX] == 3){
				ret = false;
				return ret;
			}
			if (App->player->position.x < checkX)
				checkX--;
			else if (App->player->position.x > checkX)
				checkX++;
			if (App->player->position.y < checkY)
				checkY--;
			else if (App->player->position.y > checkY)
				checkY++;
		}
	}
	return ret;
}
void ModuleEnemies::formationOrder(int enemyNumber){
	for (int i = 0; i < MAX_ENEMIES; i++){
		if (enemies[i] != nullptr && i != enemyNumber){
			if (enemies[enemyNumber]->position.x == enemies[i]->position.x&&enemies[enemyNumber]->position.y == enemies[i]->position.y){
				if (enemies[enemyNumber]->formation == enemies[i]->formation){
					changeOrder(i);
				}
			}
		}
	}
}
void ModuleEnemies::changeOrder(int enemyNumber){
	if (enemies[enemyNumber]->formation == ONLEFT)
		enemies[enemyNumber]->formation = ONRIGHT;
	else
		enemies[enemyNumber]->formation = ONLEFT;
}
