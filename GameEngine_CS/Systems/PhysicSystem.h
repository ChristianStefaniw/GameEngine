#pragma once

#include "../Engine.h"
#include "../ECS.h"
#include "../Components.h"

class PhysicSystem : public ECS::EntitySystem
{
public:
	PhysicSystem();

	bool IsColliding(
		ECS::ComponentHandle<struct BoxCollider> touchingBox,
		ECS::ComponentHandle<struct BoxCollider> touchedBox,
		float x, float y
	);

	// collision with a rectangle
	bool IsColliding(
		ECS::ComponentHandle<struct BoxCollider> touchingBox,
		sf::RectangleShape touchedRectangle, float x, float y
	);

	bool IsColliding(
		ECS::ComponentHandle<struct BoxCollider> touchingBox,
		sf::RectangleShape touchedRectangle
	);

	bool IsColliding(
		ECS::ComponentHandle<struct BoxCollider> touchingBox,
		ECS::ComponentHandle<struct BoxCollider> touchedBox
	);


	void CheckCollisionSides(
		ECS::ComponentHandle<struct Transform> transform,
		ECS::ComponentHandle<struct BoxCollider> touchingBox,
		ECS::ComponentHandle<struct BoxCollider> touchedBox
	);

	void CheckCollision(
		ECS::ComponentHandle<struct Transform> transform,
		ECS::ComponentHandle<struct BoxCollider> touchingBox,
		sf::RectangleShape touchedRectangle
	);


	void PushEntity(
		ECS::Entity* touchingEntity,
		ECS::Entity* touchedEntity
	);

	void tick(ECS::World* world, float deltaTime) override;

	~PhysicSystem();
};

