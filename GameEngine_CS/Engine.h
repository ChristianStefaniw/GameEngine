#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include "ECS.h"

#include "Components.h"
#include "Interface/MainCamera.h"

#include "Interface/Button.h"
#include "Interface/ButtonMap.h"
#include "Interface/States.h"
#include "Interface/PauseMenu.h"

#include "Systems/RenderingSystem.h"
#include "Systems/AnimationSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/PhysicSystem.h"
#include "Systems/TileMapSystem.h"


class Engine
{
public:
	sf::RenderWindow* window;
	ECS::World* world;

	class MainCamera mainCam;
	class PauseMenu pauseMenu;

	static Engine& GetInstance(void);
	void Start(sf::RenderWindow* win);
	void AddSystem(ECS::EntitySystem* newSys);

private:
	bool bQuit;

	Engine(void);

	//Required to prevent the reference from being copied, moved, or assigned
	Engine(Engine& copy);        // hide copy constructor
	Engine(Engine&& other);		 // hide move constructor
	Engine& operator = (Engine); // hide assignment operator

	~Engine(void);

	void Update();
	void GameInactiveStateActions();
};

