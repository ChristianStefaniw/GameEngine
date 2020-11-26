#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


class Engine
{
public:
	sf::RenderWindow* window;

	static Engine& GetInstance(void);
	void Start(sf::RenderWindow* win);

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

