#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleTexture.h"
#include "ModuleStartScreen.h"
#include "ModuleLevel1.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollider.h"
#include "GUI.h"
#include "GUI_Characters.h"
#include "GUI_Movement.h"
#include "GUI_Inventory.h"
#include "ModuleEnemies.h"
#include "ModulePArticles.h"
#include "ModuleItems.h"
#include "ModuleMinigames.h"

Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = input = new ModuleInput();
	modules[i++] = render = new ModuleRender();
	modules[i++] = texture = new ModuleTextures();
	modules[i++] = audio = new ModuleAudio();
	modules[i++] = level1 = new ModuleLevel1();
	modules[i++] = minigames = new ModuleMinigames();
	modules[i++] = enemies = new ModuleEnemies();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = gui = new ModuleGui();
	modules[i++] = gui_character= new GUI_Character();
	modules[i++] = gui_movement = new GUI_Movement();
	modules[i++] = gui_inventory = new GUI_Inventory();
	modules[i++] = menu_screen = new ModuleStartScreen();
	modules[i++] = collider = new ModuleCollider();
	modules[i++] = fade = new ModuleFadeToBlack();
	modules[i++] = items = new ModuleItems();


}

Application::~Application()
{
	for (int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Deactivate modules here ----
	player->Disable();
	level1->Disable();
	enemies->Disable();
	minigames->Disable();
	// ----------------------------

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}