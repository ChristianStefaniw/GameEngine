#pragma once

#include "../Engine.h"
#include "../Interface/Button.h"

class TileMapSystem : public ECS::EntitySystem
{
public:
	TileMapSystem();

	void tick(ECS::World* world, float deltaTime);
	void addTileOnClick(bool bHasCollision, ECS::ComponentHandle<struct TileMap> tileMap);


	~TileMapSystem();
};
