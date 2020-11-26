#pragma once

#include "../ECS.h"
#include "../Engine.h"
#include "../Components.h"


class RenderingSystem : public ECS::EntitySystem{
public:
	RenderingSystem(void);
	~RenderingSystem(void);

	void tick(ECS::World* world, float detlaTime) override;


};