#include "Engine.h"

Engine& Engine::GetInstance(void)
{
	static Engine _instance;
	return _instance;
}

void Engine::Start(sf::RenderWindow* win)
{
	bQuit = false;
	window = win;

	while (window->isOpen()) {
		Update();
	}

}

void Engine::AddSystem(ECS::EntitySystem* newSys)
{
	world->registerSystem(newSys);
	world->enableSystem(newSys);
}

Engine::Engine(void)
{
}

Engine::Engine(Engine& copy)
{
}

Engine::Engine(Engine&& other)
{
}

Engine& Engine::operator=(Engine)
{
	// TODO: insert return statement here
}

Engine::~Engine(void)
{
}

void Engine::Update()
{

	sf::Event _event;

	while (window->pollEvent(_event)) {
		// "Close requested" event
		if (_event.type == sf::Event::Closed) {
			window->close();
		}
	}
	world->tick(10.0f);
}
