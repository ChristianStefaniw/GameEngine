#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "ECS.h"
#include "Components.h"

#include "Systems/RenderingSystem.h"

class Engine
{
public:
	sf::RenderWindow* window;
	ECS::World* world;

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
};

