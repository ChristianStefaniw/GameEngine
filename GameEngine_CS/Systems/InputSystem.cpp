#include "InputSystem.h"

InputSystem::InputSystem(sf::RenderWindow* win)
{
	this->window = win;
}

InputSystem::~InputSystem(){}

void InputSystem::tick(ECS::World* world, float deltaTime)
{
	GetKeyEvents(world);
}

void InputSystem::GetKeyEvents(ECS::World* world)
{
	world->each<InputController>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<InputController> input) -> void {
				input->wKey = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
				input->aKey = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
				input->sKey = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
				input->dKey = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		}
	);
}
