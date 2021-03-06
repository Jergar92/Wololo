#ifndef __MODULELEVEL1_H__
#define __MODULELEVEL1_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleLevel1 : public Module
{
public:
	ModuleLevel1();
	~ModuleLevel1();

	bool Start();
	update_status Update();
	bool CleanUp();

	void open_close_door();

public:

	int map[10][10];

	SDL_Texture* graphics = nullptr;
	SDL_Texture* test_graphics = nullptr;

	//Parallel Walls
	SDL_Rect lvl1_parallel_wall;
	SDL_Rect lvl2_parallel_wall;
	SDL_Rect lvl3_parallel_wall;
	SDL_Rect lvl4_parallel_wall;

	//Front Walls
	SDL_Rect lvl1_front_wall;
	SDL_Rect lvl2_front_wall;
	SDL_Rect lvl3_front_wall;
	SDL_Rect lvl4_front_wall;

	//Large Front Walls
	SDL_Rect lvl2_large_front_wall;
	SDL_Rect lvl3_large_front_wall;
	SDL_Rect lvl4_large_front_wall;

	//Close Wall
	SDL_Rect background_wall;

	//Doors
	SDL_Rect lvl1_right_opened_door;
	SDL_Rect lvl2_right_opened_door;
	SDL_Rect lvl3_right_opened_door;
	SDL_Rect lvl4_right_opened_door;

	SDL_Rect lvl1_left_opened_door;
	SDL_Rect lvl2_left_opened_door;
	SDL_Rect lvl3_left_opened_door;
	SDL_Rect lvl4_left_opened_door;

	SDL_Rect lvl1_closed_door;
	SDL_Rect lvl2_closed_door;
	SDL_Rect lvl3_closed_door;
	SDL_Rect lvl4_closed_door;
};

#endif