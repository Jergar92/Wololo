#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "Blue_Enemy.h"

#define MAX_ENEMIES 100

enum ENEMY_TYPES
{
	NO_TYPE,
	BLUE,
	RED,
	GREEN
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
	int hp;
	int attack;
	int defense;
	int at_delay;
	int mov_delay;
	direction dir;
};

class ModuleEnemies : public Module
{
public:
	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool AddEnemy(ENEMY_TYPES type, int x, int y, int hp, int attack, int defense, int at_delay, int mov_delay,direction direction);
	bool checkMonster(int x, int y, int i);
	bool canSeePlayer(int x, int y, int i);
	void formationOrder(int i);
	void changeOrder(int i);
	//void OnCollision(Collider* c1, Collider* c2);

	EnemyInfo queue[MAX_ENEMIES];

	Enemy* enemies[MAX_ENEMIES];

private:
	void SpawnEnemy(const EnemyInfo& info);

	SDL_Texture* sprites;
};

#endif // __ModuleEnemies_H__