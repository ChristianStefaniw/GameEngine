#pragma once

#include "ECS.h"
#include "Engine.h"
#include <iostream>

struct Transform {
public:
	ECS_DECLARE_TYPE;

	float xPos, yPos, rotation;

	Transform(float newX, float newY) : xPos(newX), yPos(newY)
	{
		this->rotation = 0.0f;
	}
};


struct Sprite2D{
public:
	ECS_DECLARE_TYPE;

	sf::Sprite picture;
	std::string texturePath;
	int width, height;

	Sprite2D(std::string name) {
		texturePath = name;
	}


}
ECS_DEFINE_TYPE(Sprite2D);
ECS_DEFINE_TYPE(Transform);