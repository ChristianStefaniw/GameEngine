#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float xPos, float yPos, float gridSizeF, bool bColliding)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color(sf::Color::Red));
	this->shape.setPosition(xPos * gridSizeF, yPos * gridSizeF);

	this->bColliding = bColliding;
}

Tile::~Tile()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

const bool &Tile::getCollision() const
{
	return this->bColliding;
}

const sf::Vector2f &Tile::getPosition() const
{
	return this->shape.getPosition();
}

std::string Tile::toString()
{
	std::stringstream stream;

	stream << this->bColliding << " ";

	return stream.str();
}
