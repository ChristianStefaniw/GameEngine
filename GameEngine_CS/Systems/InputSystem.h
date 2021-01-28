#pragma once

#include "../ECS.h"
#include "../Engine.h"
#include "../Components.h"


class InputSystem :
	public ECS::EntitySystem
{
public:
	InputSystem(sf::RenderWindow* win);
	~InputSystem();

	void tick(ECS::World* world, float deltaTime) override;
	void GetKeyEvents(ECS::World* world);

private:
	sf::RenderWindow* window;

};

