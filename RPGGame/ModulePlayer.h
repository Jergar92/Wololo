#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Vector.h"
#include "String.h"
#include "DoubleList.h"
#include "ModuleItems.h"

struct SDL_Texture;
#define NUM_PLAYERS 4
#define MAX_INVENTORY_SLOTS 9
#define MAX_EQUIPED_SLOTS 3

enum player_class{
	WARRIOR,
	ROGUE,
	ARCHER,
	MAGE
};
enum Attack_State{
	READY,
	COOLDOWN
};

enum direction{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

enum rotation{
	RIGHT,
	LEFT
};

class Player{
public:
	Player(String name, int max_hp, int hp, int max_mp, int mp, int attack, int defense, uint cd_count, uint spc_cd_count) :name(name), max_hp(max_hp), hp(hp), max_mp(max_mp), mp(mp), attack(attack), defense(defense), cd_count(cd_count), spc_cd_count(spc_cd_count) {}
	~Player(){}
	String name;
	Attack_State MyAttack = READY;
	Attack_State MySpecialAttack = READY;
	int max_hp, hp,max_mp, mp, attack, defense;
	uint cd_count, spc_cd_count;
	bool PlayerDead = false;
	DoubleList<Item*> inventory;
};

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Vector<Player*> formation;

	SDL_Texture* g_corridor = nullptr;
	SDL_Texture* g_corridorv1 = nullptr;
	SDL_Texture* g_directions = nullptr;
	SDL_Texture* g_directionsv1 = nullptr;
	SDL_Texture* g_background1 = nullptr;
	SDL_Texture* direct = nullptr;
	SDL_Texture* g_exit = nullptr;

	iPoint position;
	SDL_Rect corridor;
	SDL_Rect corridorv1;
	SDL_Rect directions;
	SDL_Rect directionsv1;
	SDL_Rect background1;
	SDL_Rect test;
	SDL_Rect exit;
	SDL_Rect compass;

	direction dir;
	int room_tile[4];
	int back_room_tile;
	bool cant_cross = false;
	bool PlayerCanPass(int, int);
	void PlayerInput();
	void PlayerRotation(int, rotation);
	void ChangeTile(int);
	void CompassPrint(int);
	void GetItem(Item* item,int player);
	void PlayerAttack(int, int);
	void PlayerSpecialAttack(int, int);
};

#endif




/*	

	background_wall = { 0, 0, 600, 600 };
	lvl1_front_wall = { 0, 0, 600, 600 };
	lvl2_front_wall = { 600, 0, 600, 600 };
	lvl1_parallel_wall = { 1200, 0, 600, 600 };
	lvl2_large_front_wall = { 0, 600, 360, 360 };
	lvl2_parallel_wall = { 360, 600, 360, 360 };
	lvl3_front_wall = { 720, 600, 360, 360 };
	lvl3_large_front_wall = { 0, 960, 215, 215 };
	lvl3_parallel_wall = { 215, 960, 215, 215 };
	lvl4_front_wall = { 430, 960, 215, 215 };
	lvl4_large_front_wall = { 0, 1175, 135, 135 };
	lvl4_parallel_wall = { 135, 1175, 135, 135 };
	
	*/