#pragma once

#include "ECS.h"
#include "Engine.h"
#include <iostream>

struct Transform {
public:
	ECS_DECLARE_TYPE;

	float xPos, yPos, rotation, xSpeed, ySpeed, xSpeedMod, ySpeedMod;

	Transform(float newX, float newY, float newXSpeed = 0.0f, float newYSpeed = 0.0f)
		: xPos(newX), yPos(newY), xSpeedMod(newXSpeed), ySpeedMod(newYSpeed)
	{
		this->rotation = 0.0f;
		this->xSpeed = 0.0f;
		this->ySpeed = 0.0f;
	}

	void UpdateSpeed(float x, float y) {
		this->xSpeed = x;
		this->ySpeed = y;
	}

	void Move() {
		// halve the speed when moving diagnolly
		if (xSpeed != 0 && ySpeed != 0) {
			xSpeed /= 2;
			ySpeed /= 2;
		}

		xPos += xSpeed;
		yPos += ySpeed;
	}
};


struct Sprite2D {
public:
	ECS_DECLARE_TYPE;

	sf::Sprite picture;
	std::string texturePath;
	int width, height;

	Sprite2D(std::string name) {
		texturePath = name;
	}
};

struct Animator{
	ECS_DECLARE_TYPE;

	int spriteWidth, spriteHeight;
	int currentColumn, currentRow;
	int totalColumns, totalRows;

	float currentTime, nextFrameTime;

	bool bFacingRight;

	Animator(int newWidth, int newHeight, float timeBetweenFrames, int newColumns, int newRows)
	{
		this->spriteWidth = newWidth;
		this->spriteHeight = newHeight;

		currentColumn = 0;
		currentRow = 0;

		this->totalColumns = newColumns;
		this->totalRows = newRows;

		this->nextFrameTime = timeBetweenFrames;

		currentTime = 0;
		
		bFacingRight = true;
	}
};

struct InputController {
public:
	ECS_DECLARE_TYPE;

	bool bInputActive;

	bool wKey, aKey, sKey, dKey;

	InputController() {
		bInputActive = true;
		wKey = false;
		aKey = false;
		sKey = false;
		dKey = false;
	}

};

struct BoxCollider {
public:
	ECS_DECLARE_TYPE;

	int leftEdge, rightEdge, topEdge, bottomEdge;

	BoxCollider() {
		leftEdge = 0;
		rightEdge = 0;
		topEdge = 0;
		bottomEdge = 0;
	}

	void Update(int xSide, int ySide, int width, int height) {
		leftEdge = xSide;
		rightEdge = xSide + width;
		topEdge = ySide;
		bottomEdge = ySide + height;
	}
};

struct Camera {
public:
	ECS_DECLARE_TYPE;

	sf::View cameraView;

	Camera(sf::Vector2f pivot) {
		cameraView.setCenter(pivot);
	}
};


ECS_DEFINE_TYPE(InputController);
ECS_DEFINE_TYPE(Sprite2D);
ECS_DEFINE_TYPE(Transform);
ECS_DEFINE_TYPE(Animator);
ECS_DEFINE_TYPE(Camera);
