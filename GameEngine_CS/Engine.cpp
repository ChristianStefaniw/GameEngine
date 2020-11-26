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
	while (window.pollEvent(_event)) {
		// "Close requested" event
		if (_event.type == sf::Event::Closed) {
			window.close();
		}
	}
}
