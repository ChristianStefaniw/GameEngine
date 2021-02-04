#include "PauseMenu.h"

PauseMenu::PauseMenu(){}

PauseMenu::PauseMenu(sf::RenderWindow* window)
{
	States::SetPausedState(false);
	InitButtons();
}

PauseMenu::~PauseMenu() {}

void PauseMenu::Update(sf::Event event, float deltaTime, sf::RenderWindow* window)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			States::SetPausedState(States::GetPausedState() == false);
		}
	}

	// TODO: Finish implementation
}

void PauseMenu::Render(sf::RenderWindow* window, float deltaTime, sf::Vector2f resumePosition) 
{

}

void PauseMenu::InitButtons()
{
	sf::Vector2f _size = sf::Vector2f(125, 30);

	ButtonMap::GetMap().insert(
		{
			"RESUME",
			new Button(_size, sf::Color(100, 100, 100, 255), "Resume Game")
		});
	ButtonMap::GetMap().insert(
		{
			"LOAD",
			new Button(_size, sf::Color(100, 100, 100, 255), "Load TileMap")
		});

	ButtonMap::GetMap().insert(
		{
			"SAVE",
			new Button(_size, sf::Color(100, 100, 100, 255), "Save TileMap")
		});

	ButtonMap::GetMap().insert(
		{
			"QUIT",
			new Button(_size, sf::Color(100, 100, 100, 255), "Quit Game")
		});
}

void PauseMenu::Quit(sf::RenderWindow* window) {
	window->close();
}