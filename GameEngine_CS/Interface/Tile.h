#pragma once

#include <iostream>
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Tile
{
public:
	bool bColliding;
	sf::RectangleShape shape;

	Tile();
	Tile(float xPos, float yPos, float gridSizeF, bool bColliding);
	~Tile();

	void render(sf::RenderTarget& target);
	const bool& getCollision() const;
	const sf::Vector2f& getPosition() const;
	std::string toString();
};

